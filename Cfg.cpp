#include"Cfg.h"

Cfg& Cfg::GetInstance()
{
	static Cfg cfg;
	return cfg;
}

void Cfg::Parse(char * _filename)
{
	delete importer;
	importer = new json_importer(_filename);
}

void Cfg::SetVariables()
{
	knight_symbol = importer->get_char("knight", "symbol");
	princess_symbol = importer->get_char("princess", "symbol");
	zombie_symbol = importer->get_char("zombie", "symbol");
	dragon_symbol = importer->get_char("dragon", "symbol");
	wizard_symbol = importer->get_char("wizard", "symbol");
	dragon_nest_symbol = importer->get_char("dragon_nest", "symbol");
	cemetery_symbol = importer->get_char("cemetery", "symbol");
	wall_symbol = importer->get_char("wall", "symbol");
	emptiness_symbol = importer->get_char("emptiness", "symbol");
	medkit_symbol = importer->get_char("medkit", "symbol");

	knight_hp = importer->get_int("knight", "hp");
	zombie_hp = importer->get_int("zombie", "hp");
	dragon_hp = importer->get_int("dragon", "hp");
	princess_hp = importer->get_int("princess", "hp");
	wizard_hp = importer->get_int("wizard", "hp");

	knight_dmg = importer->get_int("knight", "damage");
	zombie_dmg = importer->get_int("zombie", "damage");
	dragon_dmg = importer->get_int("dragon", "damage");
	wizard_dmg = importer->get_int("wizard", "damage");
	fireball_dmg = importer->get_int("fireball", "damage");

	cemetery_cooldown = importer->get_int("cemetery", "cooldown");
	dragon_nest_cooldown = importer->get_int("dragon_nest", "cooldown");
	medkit_cooldown = importer->get_int("medkit", "cooldown");

	medkit_max_count = importer->get_int("medkit", "max_count");

	medkit_heal_power = importer->get_int("medkit", "heal_power");
}

Cfg::~Cfg()
{
	delete importer;
}

Cfg::Cfg(void)
{

}
