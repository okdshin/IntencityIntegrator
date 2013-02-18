#ifdef INTENSITYINTEGRATOR_UNIT_TEST
#include "IntensityIntegrator.h"
#include <iostream>
using namespace none;

int main(int argc, char* argv[])
{
	unsigned int intencity_column_index = 7;
	boost::filesystem::path dal_file_name = "sample_data/d1-ave32-circle+50+150.dal";
	boost::filesystem::path result_csv_file_name = "result.csv";
	if(argc > 3){
		intencity_column_index = boost::lexical_cast<unsigned int>(argv[3]);	
	}
	if(argc > 2){
		dal_file_name = argv[1];
		result_csv_file_name = argv[2];
	}
	if(argc <= 2){
		std::cout << "too few arguments!\nhow to use:\n";
		std::cout << " <dal file name> <save file name> (<intencity index(default is 7)>)" << std::endl;
		return 0;
	}
	std::cout << boost::format("dal file:%1%\nsave file:%2%\nintencity index:%3%\n") 
		% dal_file_name
		% result_csv_file_name
		% intencity_column_index
	<< std::endl;

	IntegrateIntencity(
		intencity_column_index, 
		dal_file_name, result_csv_file_name);

	return 0;

}

#endif
