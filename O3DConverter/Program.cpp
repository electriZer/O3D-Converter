/**
	Copyright 2017 Jiyan Akgül

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http ://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#include "stdafx.h"
#include "O3D.h"
#include <assimp\scene.h>
#include <assimp\Exporter.hpp>
#include "O3DImporter.h"


void replace(const std::string& from, const std::string& to, std::string& str)
{
	size_t pos;
	while ((pos = str.find(from)) != std::string::npos)
		str.replace(pos, from.size(), to);
}

int main(int argv,char* args[])
{
#if defined _DEBUG
	if (!IsDebuggerPresent())
	{
		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
		_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	}
#endif
	// Default output file format and extension
	std::string format = "obj";
	std::string extension = ".obj";
	//  Argument "as_collada" is set
	if (argv == 5) {
		format = "collada";
		extension = ".dae";
	}
	// Wrong number of arguments
	else if (argv != 4) { 
		std::cout << "Usage : O3D.exe src.o3d TextureFolder OutputFolder [as_collada ] \n as_collada - '1' for output as .dae or empty for wavefront .obj\n";
		if (argv > 0)
			std::cout << "count" << argv << ",first : " << args[0];
		return -1; 
	}
	// Parse Filename
	std::string filename = std::string(args[1]);
	std::string input_ext = filename.substr(filename.find_last_of('.'),filename.length()-1);
	std::string TextureFolder = std::string(args[2]);
	std::string OutputFolder = std::string(args[3]);

	// Remove comments to traverse a path and convert each file
	/*for (auto & p : std::experimental::filesystem::v1::directory_iterator(path))
	{*/
			//if (/*p.path().filename().string().compare(0, 3, "Mvr") == 0 &&*/ p.path().extension().compare(".o3d") == 0) {
			if(input_ext.compare(".o3d")==0){
			//std::cout << p.path().filename() << std::endl;
				try {
					O3DImporter Importer(filename,TextureFolder, OutputFolder);

					// Export File
					auto name = std::string(Importer.scene->mRootNode->mName.C_Str());
					std::string final_path = std::string(OutputFolder + "\\" + name + extension).c_str();
					Assimp::Exporter().Export(Importer.scene, format,final_path);
				}
				catch (std::exception e) {
					std::cout << "Exception while exporting '" << filename << "'";
					//continue;
				}
			}
			else {
				std::cout << "Wrong File Ending - expteded '.o3d'; got '"+input_ext+"'";
				printf("WRONG FILE FORMAT '%s'!=.o3d", input_ext);;
			}
		//}
	return 0;

}
