#include "material.hpp"

void Vin::Material::Bind()
{
    m_Program->Bind();
    for (usize i = 0; i < 16; ++i)
        if (m_Textures[i].used)
            m_Textures[i].texture->Bind(i);
}

int Vin::Material::GetField(const char* name)
{
    return m_Program->GetField(name);
}

void Vin::Material::SetFloat(int location, float value)
{
    m_Program->SetFloat(location, value);
}

void Vin::Material::SetFloat2(int location, float* values)
{
    m_Program->SetFloat2(location, values);
}

void Vin::Material::SetFloat3(int location, float* values)
{
    m_Program->SetFloat3(location, values);
}

void Vin::Material::SetFloat4(int location, float* values)
{
    m_Program->SetFloat4(location, values);
}

void Vin::Material::SetFloats(int location, float* values, size_t count)
{
    m_Program->SetFloats(location, values, count);
}

void Vin::Material::SetInt(int location, int value)
{
    m_Program->SetInt(location, value);
}

void Vin::Material::SetInt2(int location, int* values)
{
    m_Program->SetInt2(location, values);
}

void Vin::Material::SetInt3(int location, int* values)
{
    m_Program->SetInt3(location, values);
}

void Vin::Material::SetInt4(int location, int* values)
{
    m_Program->SetInt4(location, values);
}

void Vin::Material::SetInts(int location, int* values, size_t count)
{
    m_Program->SetInts(location, values, count);
}

void Vin::Material::SetMat3(int location, float* values)
{
    m_Program->SetMat3(location, values);
}

void Vin::Material::SetMat4(int location, float* values)
{
    m_Program->SetMat4(location, values);
}

void Vin::Material::SetTexture(int location, eastl::shared_ptr<Texture> texture)
{
    m_Textures[location].texture = texture;
    m_Textures[location].used = true;
}

eastl::shared_ptr<Vin::Material> Vin::Material::Create(eastl::shared_ptr<Program> program)
{
    return eastl::make_shared<Material>(program);
}