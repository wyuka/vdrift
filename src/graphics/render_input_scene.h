/************************************************************************/
/*                                                                      */
/* This file is part of VDrift.                                         */
/*                                                                      */
/* VDrift is free software: you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or    */
/* (at your option) any later version.                                  */
/*                                                                      */
/* VDrift is distributed in the hope that it will be useful,            */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/* GNU General Public License for more details.                         */
/*                                                                      */
/* You should have received a copy of the GNU General Public License    */
/* along with VDrift.  If not, see <http://www.gnu.org/licenses/>.      */
/*                                                                      */
/************************************************************************/

#ifndef _RENDER_INPUT_SCENE_H
#define _RENDER_INPUT_SCENE_H

#include "render_input.h"
#include "mathvector.h"
#include "quaternion.h"
#include "matrix4.h"
#include "frustum.h"
#include "reseatable_reference.h"
#include <vector>

class SCENENODE;
class DRAWABLE;
class TEXTURE_INTERFACE;
class SHADER_GLSL;

class RENDER_INPUT_SCENE : public RENDER_INPUT
{
public:
	RENDER_INPUT_SCENE();

	~RENDER_INPUT_SCENE();

	void SetDrawLists(
		const std::vector <DRAWABLE*> & dl_dynamic,
		const std::vector <DRAWABLE*> & dl_static);

	void DisableOrtho();

	void SetOrtho(
		const MATHVECTOR <float, 3> & neworthomin,
		const MATHVECTOR <float, 3> & neworthomax);

	FRUSTUM SetCameraInfo(
		const MATHVECTOR <float, 3> & newpos,
		const QUATERNION <float> & newrot,
		float newfov, float newlodfar,
		float neww, float newh,
		bool restore_matrices = true);

	void SetSunDirection(const MATHVECTOR <float, 3> & newsun);

	void SetFlags(bool newshaders);

	void SetDefaultShader(SHADER_GLSL & newdefault);

	void SetClear(bool newclearcolor, bool newcleardepth);

	virtual void Render(GLSTATEMANAGER & glstate, std::ostream & error_output);

	void SetReflection(TEXTURE_INTERFACE * value);

	void SetFSAA(unsigned int value);

	void SetAmbient(TEXTURE_INTERFACE & value);

	void SetContrast(float value);

	void SetDepthMode(int mode);

	void SetWriteDepth(bool write);

	void SetWriteColor(bool write);

	void SetWriteAlpha(bool write);

	std::pair <bool, bool> GetClear() const;

	void SetCarPaintHack(bool hack);

	void SetBlendMode(BLENDMODE::BLENDMODE mode);

private:
	reseatable_reference <const std::vector <DRAWABLE*> > dynamic_drawlist_ptr;
	reseatable_reference <const std::vector <DRAWABLE*> > static_drawlist_ptr;
	bool last_transform_valid;
	MATRIX4 <float> last_transform;
	QUATERNION <float> cam_rotation; //used for the skybox effect
	MATHVECTOR <float, 3> cam_position;
	MATHVECTOR <float, 3> lightposition;
	MATHVECTOR <float, 3> orthomin;
	MATHVECTOR <float, 3> orthomax;
	float w, h;
	float camfov;
	FRUSTUM frustum; //used for frustum culling
	float lod_far; //used for distance culling
	bool shaders;
	bool clearcolor, cleardepth;
	reseatable_reference <SHADER_GLSL> shader;
	reseatable_reference <TEXTURE_INTERFACE> reflection;
	reseatable_reference <TEXTURE_INTERFACE> ambient;
	bool orthomode;
	unsigned int fsaa;
	float contrast;
	int depth_mode;
	bool writecolor;
	bool writealpha;
	bool writedepth;
	bool carpainthack;
	bool vlighting;
	BLENDMODE::BLENDMODE blendmode;

	void DrawList(GLSTATEMANAGER & glstate, const std::vector <DRAWABLE*> & drawlist, bool preculled);

	/// returns true if the object was culled and should not be drawn
	bool FrustumCull(DRAWABLE & tocull);

	void SelectAppropriateShader(DRAWABLE & forme);

	void SelectFlags(DRAWABLE & forme, GLSTATEMANAGER & glstate);

	void SelectTexturing(DRAWABLE & forme, GLSTATEMANAGER & glstate);

	bool SelectTransformStart(DRAWABLE & forme, GLSTATEMANAGER & glstate);

	void SelectTransformEnd(DRAWABLE & forme, bool need_pop);
};

#endif // _RENDER_INPUT_SCENE_H
