#include "Engine.hpp"
#include "IO/Commands/CreateMap.hpp"
#include "IO/Commands/March.hpp"
#include "IO/Commands/SpawnHunter.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"
#include "IO/Events/UnitAttacked.hpp"
#include "IO/System/CommandParser.hpp"
#include "IO/System/EventLog.hpp"
#include "IO/System/PrintDebug.hpp"
#include "IO/System/TypeRegistry.hpp"
#include "System/EventProducer.hpp"
#include "Util/Factories.hpp"

#include <ResourceRegistry.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	auto& engine = core::Engine::instance();

	auto eventLog = std::make_shared<EventLog>();
	auto producer = std::make_shared<io::EventProducer>();

	std::cout << "Commands:\n";
	io::CommandParser parser;
	parser
		.add<io::CreateMap>(
			[&producer](auto command)
			{
				printDebug(std::cout, command);
				producer->append(std::make_shared<io::CreateMap>(command));
			})
		.add<io::SpawnSwordsman>(
			[&producer](auto command)
			{
				printDebug(std::cout, command);
				producer->append(std::make_shared<io::SpawnSwordsman>(command));
			})
		.add<io::SpawnHunter>(
			[&producer](auto command)
			{
				printDebug(std::cout, command);
				producer->append(std::make_shared<io::SpawnHunter>(command));
			})
		.add<io::March>(
			[&producer](auto command)
			{
				printDebug(std::cout, command);
				producer->append(std::make_shared<io::March>(command));
			});

	parser.parse(file);

	engine.setLogger(std::move(eventLog));
	engine.setObjectRegistry(core::makeObjectRegistry());

	std::cout << "\n\nEvents:\n";

	engine.initialize(producer);
	engine.run();

	return 0;
}
