#ifndef SHADER_H
#define SHADER_H

#include "../glad/include/glad/glad.h" // inclusão da biblioteca glad para usar o OpenGL
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  

class Shader
{
public:
    // id do programa
    unsigned int ID;
  
    // contrutor do shader
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // string aonde ficara armazenado codigo fonte do shader de vertice
        std::string vertexCode;

        // string aonde ficara armazenado codigo fonte do shader de fragmento
        std::string fragmentCode;

        // variavel do arquivo de vertice
        std::ifstream vShaderFile;

        // variavel do arquivo de fragmento
        std::ifstream fShaderFile;

        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            // abre os codigos de shaders
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);

            // cria um buffer para os codigos
            std::stringstream vShaderStream, fShaderStream;

            // escreve os valores dos arquivos nos buffers
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // fecha os codigos de shaders
            vShaderFile.close();
            fShaderFile.close();

            // retem os valores dos buffers tranformados em strings em suas respectivas strings
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }

        // caso as operações no bloco anterior derem errado será imprimido um erro
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        // armazena o codigo dos shader em string em arrays do tipo char terminadas em nulo 
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];
        
        // criação e compilação do shader de vertice
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        // imprime erros de compilação caso haja algum
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
        
        // criação e compilação do shader de fragmento
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        // imprime erros de compilação caso haja algum
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
        
        // criação do programa de shader
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        // imprime erros caso o ligamento de errado
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        
        // deleta shaders que ja estão ligados no programa e não seram mais usados
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    // função ativadora de shader
    void use()
    {
        glUseProgram(ID);
    }

    // função uniform
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    } 
};
  
#endif
