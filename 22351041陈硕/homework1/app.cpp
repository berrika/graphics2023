#include "app.h"
#include "camera.h"
//libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//std
#include <stdexcept>
#include <array>
#include <chrono>
#include <iostream>

const float MAX_FRAME_TIME = 1;

App::App(){}

App::~App() {}

void App::run()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glViewport(0, 0, WIDTH, HEIGHT);
    //Camera camera;
    //camera.setViewDirection(glm::vec3(0.f), glm::vec3(0.5f, 0.f, 1.f));
    //camera.setViewTarget(glm::vec3(-1.f, -2.f, 2.f), glm::vec3(0.f, 0.f, 2.5f));
    auto currentTime = std::chrono::high_resolution_clock::now();
    Shader shader{ "vertshader.vert", "fragshader.frag" };
    // ���ö�������
    float vertices[] = {
        // λ��              // ��ɫ
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // left  
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // right 
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top   
    };
    // ����һ�������������VAO��һ�����㻺�����VBO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // ��VAO����VBO��GL_ARRAY_BUFFERĿ���ϣ���EBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // ���������鸴�Ƶ������й�OpenGLʹ��
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // ���ö�������ָ��
    // λ������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // ��ɫ����
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    while (!window.shouldClose())
    {
        auto newTime = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;
        //to avoid auto move when changing window size
        frameTime = glm::min(frameTime, MAX_FRAME_TIME);
        //��鰴���Ƿ���
        window.processInput();
		//��Ⱦָ��
		//glClearColor���������Ļ���õ���ɫ----״̬���ú���
		//glClear���������ɫ����֮����Ļ�����ΪglClearColor�е���ɫ��---״̬ʹ�ú���
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	
		glClear(GL_COLOR_BUFFER_BIT);
        //draw
        shader.use();
        shader.setFloat("someUniform", 1.0f);   
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
		//�������¼�����������
		//˫���壺ǰ�滺��һ�Ż���������ʾ����̨����⻺����һ�ţ�����һ�Ž�����ֱ�ӽ�����Ч���ϱ㲻�����������л��ƴ�����������
		glfwSwapBuffers(window.getGLFWwindow());//������ɫ����
		glfwPollEvents();//�����꣬���̣����´���״̬�������ö�Ӧ�Ļص�������
    }
    //delete

    //�˳�glfw
    glfwTerminate();
}

