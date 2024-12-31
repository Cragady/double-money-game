#include "YamlTest/YamlTest.hpp"

#include <yaml-cpp/yaml.h>

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>

#include "yaml-cpp/node/parse.h"

const int BYTE_1024 = 1024;

YamlTest::YamlTest() { Run(); }

void YamlTest::Run() {
  std::cout << "Success" << std::endl;

  // std::ofstream find_me("find_me.txt");
  // find_me << "Could you do it boo? <3" << std::endl;
  // find_me.close();

  YAML::Node primes = YAML::Load("[2, 3, 5, 7, 11]");
  for (std::size_t i = 0; i < primes.size(); i++) {
    std::cout << primes[i].as<int>() << "\n";
  }

  YAML::Node object_file = YAML::LoadFile("assets/test/yaml/GameStuff.yaml");
  // for (std::size_t i = 0; i < config.size(); i++) {
  //   std::cout << config[0] << std::endl;
  // }

  std::ofstream fout("assets/test/yaml/GameStuff.yaml");
  fout << object_file;
  fout.close();

  YAML::Node new_object;
  new_object["name"] = "Test Button 2";
  new_object["position"]["x"] = 3.3;
  new_object["position"]["y"] = 4.5;
  new_object["position"]["z"] = -5.0;
  new_object["rotation"]["x"] = 0;
  new_object["rotation"]["y"] = 0;
  new_object["rotation"]["z"] = 0;
  new_object["rotation"]["w"] = 1.0;
  new_object["size"]["x"] = 1;
  new_object["size"]["y"] = 1;
  new_object["size"]["z"] = 1;

  fout.open("assets/test/yaml/NewObject.yaml");
  fout << new_object;
  fout.close();

  YAML::Node scene_1 = YAML::LoadFile("assets/test/yaml/Scene1.yaml");

  YAML::Node object_files = scene_1["objects"];

  YAML::Node objects[BYTE_1024];

  std::size_t files_num = object_files.size();
  for (std::size_t i = 0; i < files_num && files_num < BYTE_1024; i++) {
    const std::string file_name = object_files[i].as<std::string>();
    std::cout << "\n\nFile Name: " << file_name << std::endl;
    objects[i] = YAML::LoadFile(file_name);
    std::cout << "File loaded." << std::endl;

    YAML::Node current = objects[i];

    std::cout << "Name: " << current["name"].as<std::string>() << std::endl;
    // NOTE: the '.as<float>()' conversions here are not necessary.
    // Just showing.
    std::cout << "Pos: { x: " << current["position"]["x"].as<float>();
    std::cout << ", y: " << current["position"]["y"].as<float>();
    std::cout << ", z: " << current["position"]["z"].as<float>() << " }"
              << std::endl;
  }

  // NOTE: works
  // FILE *testing = fopen("assets/test/yaml/test-file.txt", "w");
  // if (!testing) {
  //   std::cout << "Failed to open/create file" << std::endl;
  //   return;
  // }
  // fprintf(testing, "This is the the test");
  // fclose(testing);
}
