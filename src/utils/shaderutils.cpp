#include "shaderutils.hpp"

#include "assets/asset.hpp"

std::string SolveInclude(Vin::Asset<std::string> shader) {
	std::string solved{ *shader.Get() };

	for (
		size_t pos = solved.find("#include", 0);
		pos != std::string::npos; 
		pos = solved.find("#include", 0)) {

		size_t beg = solved.find('"', pos) + 1;
		size_t end = solved.find('"', beg);

		std::string path = solved.substr(beg, end - beg);

		Vin::Asset<std::string> include = Vin::AssetDatabase::LoadAsset<std::string>(path);

		solved.replace(pos, end - pos, *include.Get());
	}

	return solved;
}

std::shared_ptr<Vin::Program> Vin::LoadProgram(std::string_view vspath, std::string_view fspath)
{
	std::shared_ptr<Vin::Program> program = Vin::Program::Create();

	Vin::Asset<std::string> vsfile = Vin::AssetDatabase::LoadAsset<std::string>(std::string{ vspath });
	Vin::Asset<std::string> fsfile = Vin::AssetDatabase::LoadAsset<std::string>(std::string{ fspath });

	program->AddShader(Vin::ShaderType::VertexShader, SolveInclude(vsfile).data());
	program->AddShader(Vin::ShaderType::FragmentShader, SolveInclude(fsfile).data());

	program->CompileProgram();

	Vin::AssetDatabase::Unload(vsfile);
	Vin::AssetDatabase::Unload(fsfile);
	
	return program;
}
