#include "Material.h"

void Material::setUniforms(Shader& targetShader)
{
	

	bool NormalMapUse = false;

	if (NormalMap.TextureSelected != nullptr) {
		NormalMapUse = NormalMap.TextureSelected->created;
		size_t NM = NormalMap.Bind(true);
		if (NormalMapUse) targetShader.setUniform("objMaterial.NormalMap", NM);
	}
	targetShader.setUniform("objMaterial.UseNormalMap", NormalMapUse);

	size_t CM = colorMap.Bind(true);
	targetShader.setUniform("objMaterial.ColorMap", CM);
}

void Material::disable()
{
	colorMap.Bind(false);
	if (NormalMap.TextureSelected != nullptr) NormalMap.Bind(false);
}
