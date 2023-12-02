#include "Item.h"

#include <picojson.h>
#include "json_utils.h"

bool Item::from_json(const std::string & filename, picojson::object & json_obj) {


	// this is where you will implement the loader for your Item
	// obviously, the item will have the common properties in GameObject, so we do that
	// super class method first
	
	if (!has_field<bool>(json_obj, "Takeable")){
		std::cerr << "filename : " << filename << "does not contain a Takeable boolean";
		return false;
	}
        if (!has_field<bool>(json_obj, "Moveable")){
                std::cerr << "filename : " << filename << "does not contain a Moveable boolean";
                return false;
        }
	else {
		//return GameObject::from_json(filename, json_obj);
        	id = json_obj["Id"].get<std::string>();
        	name = json_obj["Name"].get<std::string>();
        	description = json_obj["Description"].get<std::string>();
		takeable = json_obj["Takeable"].get<bool>();
		moveable = json_obj["Moveable"].get<bool>();
		//std::cout << "takeable: ";
		//std::cout << takeable;
		//std::cout << "\n";
		//std::cout << "moveable: ";
		//std::cout << moveable;
		//std::cout << "\n";

		return true;
	}

	// but then, you will need to load the additional properties from json
	// for the instance variables (properties) that you have defined in Item.h 
	// as protected member variables
	

}


