#include "../header/Instructions.h"
#include "../header/ServiceLocator.h"
#include "../header/GraphicService.h"

Instructions::Instructions()
{
    instructions = nullptr;
}

Instructions::~Instructions()
{
    onDestroy();
}

void Instructions::initialize()
{
    initializeInstructions();
}

void Instructions::update()
{
}

void Instructions::render()
{
    drawInstructions();
}

void Instructions::initializeInstructions()
{
    instructions = new sf::String[number_of_instructions]();

    instructions[0] = instruction_string_one;
    instructions[1] = instruction_string_two;
    instructions[2] = instruction_string_three;
    instructions[3] = instruction_string_four;
    instructions[4] = instruction_string_five;
    instructions[5] = instruction_string_six;
    instructions[6] = instruction_string_seven;
}

void Instructions::drawInstructions()
{
    for (int i = 0; i < number_of_instructions; i++)
    {
        ServiceLocator::getInstance()->getGraphicService()->drawText(instructions[i], top_offset + (text_spacing * i), font_size);
    }
}

void Instructions::onDestroy()
{
    delete[] instructions;
}