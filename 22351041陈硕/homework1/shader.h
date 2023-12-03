#pragma once
#include <string>

class Shader
{
private:
    // ����ID
    unsigned int ID;
    //�����ɫ�������Ƿ���롢���ӳɹ�
    void checkCompileErrors(unsigned int ID, std::string type);
public:
    // ��ȡ������shader�ļ��ĺ���
    Shader(const char* vertexPath, const char* fragmentPath);
    // ʹ��shader�ļ��ĺ���
    void use();
    // uniform���ߺ���
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
};
