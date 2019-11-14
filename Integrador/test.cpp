#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <unordered_map>

#include "IDatabaseHandler.h"
#include "SqliteDatabaseHandler.h"

std::string uuid()
{
	return "550e8400-e29b-41d4-a716-446655440000";
};

//Data-Entities
struct Town
{
	int64_t id;
	std::string uuid;
	std::string name;
	std::string postal_code;
	int64_t districts_id;
};

struct District
{
	int64_t id;
	std::string uuid;
	std::string name;
	int64_t code;
	int64_t provinces_id;
};

struct Province
{
	int64_t id;
	std::string uuid;
	std::string name;
	std::string code;
};

//Persistance Functions

void persist( IDatabaseHandler* dbh, const Town& input )
{
	dbh->prepareQuery("INSERT INTO Towns(id,uuid,name,postal_code,districts_id) VALUES(?,?,?,?,?)");
	dbh->addParameter(1, std::to_string(input.id) );
	dbh->addParameter(2, uuid() );
	dbh->addParameter(3, input.name );
	dbh->addParameter(4, input.postal_code );
    dbh->addParameter(5, std::to_string(input.districts_id) );    
    dbh->execute();
};

void persist( IDatabaseHandler* dbh, const District& input )
{
	
	dbh->prepareQuery("INSERT INTO Districts(id,uuid,name,code,provinces_id) VALUES(?,?,?,?,?)");
	dbh->addParameter(1, std::to_string(input.id) );
	dbh->addParameter(2, uuid() );
	dbh->addParameter(3, input.name );
	dbh->addParameter(4, std::to_string(input.code) );
    dbh->addParameter(5, std::to_string(input.provinces_id) );    
    dbh->execute();
};

void persist( IDatabaseHandler* dbh, const Province& input )
{
	dbh->prepareQuery("INSERT INTO Provinces(id,uuid,name,code) VALUES(?,?,?,?)");
	dbh->addParameter(1, std::to_string(input.id) );
	dbh->addParameter(2, uuid() );
	dbh->addParameter(3, input.name );
	dbh->addParameter(4, input.code );
    dbh->execute();
};



int main()
{
	//DataBase Connection
	IDatabaseHandler* dbh = new SqliteDatabaseHandler();


	//DB Structure 
	dbh->prepareQuery("CREATE TABLE IF NOT EXISTS Provinces(id INTEGER PRIMARY KEY, uuid TEXT, name TEXT, code TEXT)");
    dbh->execute();
    
    
    dbh->prepareQuery("CREATE TABLE IF NOT EXISTS Districts(id INTEGER PRIMARY KEY, uuid TEXT, name TEXT, code TEXT, provinces_id INTEGER, FOREIGN KEY(provinces_id) REFERENCES Provinces(id) )");
    dbh->execute();
    
    dbh->prepareQuery("CREATE TABLE IF NOT EXISTS Towns(id INTEGER PRIMARY KEY, uuid TEXT, name TEXT, postal_code TEXT, districts_id INTEGER, FOREIGN KEY(districts_id) REFERENCES Districts(id) )");
    dbh->execute();
    
    //Data Objects
    Province province;
    province.id = 1;
    province.name = "Buenos Aires";
    province.code = "1";
    
    District district;
    district.id = 1;
    district.name = "General Pueyrredón";
    district.provinces_id = 1;
    district.code = 1;
        
    Town town1;
    town1.id = 1;
    town1.name = "Mar del Plata";
    town1.districts_id = 1;
    town1.postal_code = "7600";
    
    Town town2;
    town2.id = 2;
    town2.name = "Batán";
    town2.districts_id = 1;
    town2.postal_code = "7601";
    
    Town town3;
    town3.id = 3;
    town3.name = "Camet";
    town3.districts_id = 1;
    town3.postal_code = "7612";
    
    //Persisting objects
    persist( dbh, province );    
    persist( dbh, district );
    persist( dbh, town1 );
    persist( dbh, town2 );
    persist( dbh, town3 );
    
    
    //Showing Provinces
    dbh->prepareQuery("SELECT * FROM Provinces");
    Table provinces = dbh->fetchAll();

	std::cout << "Provinces" << std::endl;
	
	for( auto row : provinces )
		std::cout << "id: " << row["id"] <<  " name: " << row["name"] << std::endl;
	
	std::cout << std::endl << std::endl;
	
	//Showing Districts
    dbh->prepareQuery("SELECT * FROM Districts");
    Table districts = dbh->fetchAll();

	std::cout << "Districts" << std::endl;
	
	for( auto row : districts )
		std::cout << "id: " << row["id"] <<  " name: " << row["name"] << std::endl;
	
	std::cout << std::endl << std::endl;
	
	//Showing Towns
    dbh->prepareQuery("SELECT * FROM Towns");
    Table towns = dbh->fetchAll();

	std::cout << "Towns" << std::endl;
	
	for( auto row : towns )
		std::cout << "id: " << row["id"] <<  " name: " << row["name"] << std::endl;
	
	std::cout << std::endl << std::endl;
	

    delete dbh;
    
    return 0;
}
