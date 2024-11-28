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

	bool SpecularMapUse = false;
	if (SpecularMap.TextureSelected != nullptr) {
		SpecularMapUse = SpecularMap.TextureSelected->created;
		size_t SM = SpecularMap.Bind(true);
		if (SpecularMapUse) targetShader.setUniform("objMaterial.SpecularMap", SM);
	}
	targetShader.setUniform("objMaterial.UseSpecularMap", SpecularMapUse);

	size_t CM = colorMap.Bind(true);
	targetShader.setUniform("objMaterial.ColorMap", CM);
}

void Material::disable()
{
	colorMap.Bind(false);

	if (NormalMap.TextureSelected != nullptr) NormalMap.Bind(false);
	if (SpecularMap.TextureSelected != nullptr) SpecularMap.Bind(false);
}
