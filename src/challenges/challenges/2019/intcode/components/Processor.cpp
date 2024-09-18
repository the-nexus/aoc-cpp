
#include "Processor.hpp"

using namespace aoc::challenges::intcode2019;

void Processor::Reset()
{
    m_instructionPointer = 0;
    m_hasHalted = false;
}

void Processor::Step()
{
    m_dataBus->ReadData(m_instructionPointer++, m_instruction);

    switch (GetOpcode())
    {
    case  1: Add(); break;
    case  2: Multiply(); break;
    case  3: Input(); break;
    case  4: Output(); break;
    case  5: JumpIfNotZero(); break;
    case  6: JumpIfZero(); break;
    case  7: CompareLess(); break;
    case  8: CompareEqual(); break;
    case 99: Halt(); break;
    default: break;
    }
}

void Processor::Add()
{
    address_t const parameterAddressA = GetParameterAddress(0);
    address_t const parameterAddressB = GetParameterAddress(1);
    address_t const resultAddress = GetParameterAddress(2);
    m_instructionPointer += 3;

    data_t parameterA, parameterB;
    m_dataBus->ReadData(parameterAddressA, parameterA);
    m_dataBus->ReadData(parameterAddressB, parameterB);

    data_t const result = parameterA + parameterB;
    m_dataBus->WriteData(resultAddress, result);
}

void Processor::Multiply()
{
    address_t const parameterAddressA = GetParameterAddress(0);
    address_t const parameterAddressB = GetParameterAddress(1);
    address_t const resultAddress = GetParameterAddress(2);
    m_instructionPointer += 3;

    data_t parameterA, parameterB;
    m_dataBus->ReadData(parameterAddressA, parameterA);
    m_dataBus->ReadData(parameterAddressB, parameterB);

    data_t const result = parameterA * parameterB;
    m_dataBus->WriteData(resultAddress, result);
}

void Processor::Input()
{
    address_t const parameterAddress = GetParameterAddress(0);
    m_instructionPointer += 1;

    data_t data;
    m_dataBus->ReadData(m_ioAddress, data);
    m_dataBus->WriteData(parameterAddress, data);
}

void Processor::Output()
{
    address_t const parameterAddress = GetParameterAddress(0);
    m_instructionPointer += 1;

    data_t data;
    m_dataBus->ReadData(parameterAddress, data);
    m_dataBus->WriteData(m_ioAddress, data);
}

void Processor::JumpIfNotZero()
{
    address_t const parameterAddress = GetParameterAddress(0);
    address_t const destinationAddress = GetParameterAddress(1);
    m_instructionPointer += 2;

    data_t parameter;
    m_dataBus->ReadData(parameterAddress, parameter);

    if (parameter != 0)
    {
        data_t destination;
        m_dataBus->ReadData(destinationAddress, destination);
        m_instructionPointer = static_cast<address_t>(destination);
    }
}

void Processor::JumpIfZero()
{
    address_t const parameterAddress = GetParameterAddress(0);
    address_t const destinationAddress = GetParameterAddress(1);
    m_instructionPointer += 2;

    data_t parameter;
    m_dataBus->ReadData(parameterAddress, parameter);

    if (parameter == 0)
    {
        data_t destination;
        m_dataBus->ReadData(destinationAddress, destination);
        m_instructionPointer = static_cast<address_t>(destination);
    }
}

void Processor::CompareLess()
{
    address_t const parameterAddressA = GetParameterAddress(0);
    address_t const parameterAddressB = GetParameterAddress(1);
    address_t const resultAddress = GetParameterAddress(2);
    m_instructionPointer += 3;

    data_t parameterA, parameterB;
    m_dataBus->ReadData(parameterAddressA, parameterA);
    m_dataBus->ReadData(parameterAddressB, parameterB);

    data_t const result = parameterA < parameterB ? 1 : 0;
    m_dataBus->WriteData(resultAddress, result);
}

void Processor::CompareEqual()
{
    address_t const parameterAddressA = GetParameterAddress(0);
    address_t const parameterAddressB = GetParameterAddress(1);
    address_t const resultAddress = GetParameterAddress(2);
    m_instructionPointer += 3;

    data_t parameterA, parameterB;
    m_dataBus->ReadData(parameterAddressA, parameterA);
    m_dataBus->ReadData(parameterAddressB, parameterB);

    data_t const result = parameterA == parameterB ? 1 : 0;
    m_dataBus->WriteData(resultAddress, result);
}

void Processor::Halt()
{
    m_hasHalted = true;
}

data_t Processor::GetOpcode() const
{
    return m_instruction % 100;
}

data_t Processor::GetParameterMode(data_t const parameterOffset) const
{
    data_t divider = 100;
    for (data_t i = 0; i < parameterOffset; ++i)
    {
        divider *= 10;
    }

    return (m_instruction / divider) % 10;
}

address_t Processor::GetParameterAddress(data_t const parameterOffset) const
{
    data_t destination;
    switch (GetParameterMode(parameterOffset))
    {
    case 0: return AddressModePosition(parameterOffset);
    case 1: return AddressModeImmediate(parameterOffset);
    default: break;
    }

    return AddressModePosition(parameterOffset);
}

address_t Processor::AddressModePosition(data_t parameterOffset) const
{
    data_t addressData;
    m_dataBus->ReadData(m_instructionPointer + static_cast<address_t>(parameterOffset), addressData);
    return static_cast<address_t>(addressData);
}

address_t Processor::AddressModeImmediate(data_t parameterOffset) const
{
    return m_instructionPointer + static_cast<address_t>(parameterOffset);
}
