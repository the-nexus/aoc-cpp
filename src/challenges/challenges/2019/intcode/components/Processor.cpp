
#include "Processor.hpp"

using namespace aoc::challenges::intcode2019;

void Processor::Reset()
{
    m_programCounter = 0;
    m_hasHalted = false;
}

void Processor::Step()
{
    m_serialDevice->ReadData(m_programCounter++, m_instruction);

    switch (GetOpcode())
    {
    case  1: Add(); break;
    case  2: Multiply(); break;
    case  3: Input(); break;
    case  4: Output(); break;
    case 99: Halt(); break;
    default: break;
    }
}

void Processor::Add()
{
    int const parameterAddressA = GetParameterAddress(0);
    int const parameterAddressB = GetParameterAddress(1);
    int const resultAddress = GetParameterAddress(2);
    m_programCounter += 3;

    int parameterA, parameterB;
    m_serialDevice->ReadData(parameterAddressA, parameterA);
    m_serialDevice->ReadData(parameterAddressB, parameterB);

    int const result = parameterA + parameterB;
    m_serialDevice->WriteData(resultAddress, result);
}

void Processor::Multiply()
{
    int const parameterAddressA = GetParameterAddress(0);
    int const parameterAddressB = GetParameterAddress(1);
    int const resultAddress = GetParameterAddress(2);
    m_programCounter += 3;

    int parameterA, parameterB;
    m_serialDevice->ReadData(parameterAddressA, parameterA);
    m_serialDevice->ReadData(parameterAddressB, parameterB);

    int const result = parameterA * parameterB;
    m_serialDevice->WriteData(resultAddress, result);
}

void Processor::Input()
{
    int const parameterAddress = GetParameterAddress(0);
    m_programCounter += 1;

    int data;
    m_serialDevice->ReadData(m_ioAddress, data);
    m_serialDevice->WriteData(parameterAddress, data);
}

void Processor::Output()
{
    int const parameterAddress = GetParameterAddress(0);
    m_programCounter += 1;

    int data;
    m_serialDevice->ReadData(parameterAddress, data);
    m_serialDevice->WriteData(m_ioAddress, data);
}

void Processor::Halt()
{
    m_hasHalted = true;
}

int Processor::GetOpcode() const
{
    return m_instruction % 100;
}

int Processor::GetParameterMode(int const parameterOffset) const
{
    int divider = 100;
    for (int i = 0; i < parameterOffset; ++i)
    {
        divider *= 10;
    }

    return (m_instruction / divider) % 10;
}

int Processor::GetParameterAddress(int const parameterOffset) const
{
    int parameterAddress;
    switch (GetParameterMode(parameterOffset))
    {
    case 0: // Position Mode
        m_serialDevice->ReadData(m_programCounter + parameterOffset, parameterAddress);
        break;

    case 1: // Immediate Mode
        parameterAddress = m_programCounter + parameterOffset;
        break;

    default: // ???
        m_serialDevice->ReadData(m_programCounter + parameterOffset, parameterAddress);
        break;
    }

    return parameterAddress;
}
