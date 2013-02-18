#pragma once
//IntensityIntegrator:20130113
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

namespace none
{
auto IntegrateIntencity(
		unsigned int intencity_column_index, 
		const boost::filesystem::path& dal_file_name,
		const boost::filesystem::path& result_csv_file_name) -> void {
	boost::filesystem::ifstream dal_file(dal_file_name);
	std::vector<std::string> file_name_list;
	std::vector<unsigned int> frame_max_list;
	std::string line;
	while(std::getline(dal_file, line) && !dal_file.eof()){
		std::stringstream ss(line);
		std::string file_name;
		unsigned int frame_min, frame_max;
		ss >> file_name >> frame_min >> frame_max;
		//std::cout << file_name << std::endl;
		file_name_list.push_back(file_name);
		frame_max_list.push_back(frame_max);
	}

	const auto index_max = *std::max_element(frame_max_list.begin(), frame_max_list.end());

	std::vector<std::vector<std::tuple<int, double>>> 
		index_and_intencity_list_list;
	for(const auto file_name : file_name_list){
		//std::cout << file_name << std::endl;
		boost::filesystem::ifstream file(dal_file_name.parent_path()/file_name);
		std::string line;
		std::vector<std::tuple<int, double>> index_and_intencity_list;
		while(std::getline(file, line)){
			//std::cout << line << std::endl;
			std::stringstream ss(line);
			int index;
			ss >> index;
			for(unsigned int i = 0; i < intencity_column_index-2; ++i){
				std::string temp;
				ss >> temp;
			}
			double intencity;
			ss >> intencity;
			//std::cout << index << " " << intencity << std::endl; 
			index_and_intencity_list.push_back(std::make_tuple(index, intencity));
		}
		index_and_intencity_list_list.push_back(index_and_intencity_list);
	}

	std::vector<std::vector<double>> result_column_list;
	for(const auto& index_and_intencity_list : index_and_intencity_list_list){
		std::vector<double> result_column(index_max+1);
		for(const auto& index_and_intencity : index_and_intencity_list){
			const auto index = std::get<0>(index_and_intencity);
			result_column.at(index) = std::get<1>(index_and_intencity);
		}
		result_column_list.push_back(result_column);
	}

	boost::filesystem::ofstream result_csv_file(result_csv_file_name);
	for(unsigned int x = 0; x < index_max; ++x){
		for(unsigned int y = 0; y < result_column_list.size(); ++y){
			result_csv_file << result_column_list.at(y).at(x) << " ";
		}
		result_csv_file << std::endl;
	}

	std::cout << "finished!" << std::endl;
	
}
}

