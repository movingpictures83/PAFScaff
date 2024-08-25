#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "PAFScaffPlugin.h"

void PAFScaffPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string key, value;
   ifile >> key;
   ifile >> value;
   parameters[key] = value;
 }
}

void PAFScaffPlugin::run() {
   
}

void PAFScaffPlugin::output(std::string file) {
   std::string command = "export OLDPATH=${PYTHONPATH}; export PYTHONPATH=${PYTHON2_DIST_PACKAGES}:${PYTHON2_SITE_PACKAGES}:${PYTHONPATH}; python2 plugins/PAFScaff/pafscaff/code/pafscaff.py ";
// python2 code/pafscaff.py seqin=Pseudomonas_aeruginosa_F63912_7033.fna reference=Pseudomonas_aeruginosa_PAO1_107.fna


 command += " seqin="+PluginManager::addPrefix(parameters["seqin"]);
 command += " reference="+PluginManager::addPrefix(parameters["reference"]);
 command += " threads=1 backups=F >& "+file;
 //; export PYTHONPATH=OLDPATH"; 
 std::cout << command << std::endl;

 system(command.c_str());
}

PluginProxy<PAFScaffPlugin> PAFScaffPluginProxy = PluginProxy<PAFScaffPlugin>("PAFScaff", PluginManager::getInstance());
