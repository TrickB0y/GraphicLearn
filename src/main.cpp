#include "../glad/include/glad/glad.h" // include da biblioteca glad
#include "../glfw/include/glfw/glfw3.h" // include da biblioteca OpenGL

#include "shader.h" // include da classe shader

#include <iostream>

//	prototipagens
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


int main()
{
	//inicia o glfw
	glfwInit();

	//configura a versão do opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//	caso seja para um sistema MacOs essa linha deve ser inserida
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPACT, GL_TRUE);

	//declaração da janela
	GLFWwindow* window = glfwCreateWindow(800, 600, "Glfw window", NULL, NULL);

	//mensagem de erro caso a janela não seja criada
	if (window == NULL)
	{
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();

		return -1;
	}

	//cria o contexto da janela
	glfwMakeContextCurrent(window);

	//mensagem de erro caso o GLAD nao tenha sido iniciado
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initializate GLAD" << std::endl;
		return -1;
	}

	//especifica o tamanho da render dentro da janela
	glViewport(0, 0, 800, 600);

	//função que muda o tamanho da render de acordo com a janela
	//toda vez que ela for redimencionada
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // definição dos arquivos de shader usando o objeto de shader da classe shader
    // Shader ourShader("C:/Users/procu/Documents/Dev/GraphicLearn/src/shader.vert",
    //                "C:/Users/procu/Documents/Dev/GraphicLearn/src/shader.frag");
    Shader ourShader("./shader.vert","./shader.frag");
	//declaração dos vertices do nosso objeto em uma array de float
	
	//vertices do triangulo
	float triangle[] = {
        // posições         // cores
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // base direita
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // base esquerda
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // topo
	};

	//declaração de variaveis que seram usadas no log
	int success;
	char infoLog[512];

	//declaração de um VBOs(Vertex Buffer Objects) obs: pode ter mais de um
	unsigned int VBOs[1];
	glGenBuffers(1, VBOs);

	//declaração de um VAOs(Vertex Array Objects) obs: pode ter mais de um
	unsigned int VAOs[1];
	glGenVertexArrays(1, VAOs);

	//selecionando a array atual como a VAOs[0]
	glBindVertexArray(VAOs[0]);

	//ligando o objeto de vertice VBOs[0] ao objeto de array atual(VAO[0])
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

	//definindo os dados do VBOs[0] com os vertices do triangle_one e definindo seu tipo
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	
	//a função glVertexAttribPointer define o tipo, tamanho e local de cada vertice na 
	//memoria do VAOs[0](array de objetos de vertice); no caso os atributos são do tipo
	//float, cada na vertice terá 3 atributos (eixo x, y, z)
    //e cada vertice possuirá uma cor sendo definida por 3 atributos (cor r, g, b)
    
    //definição da posição das dados dos vertices na array de objeto(VAO)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    //definição da posição dos dados de cores dos vertices no objeto de array(VAO)
    //obs: são definidos depois dos dados de posição de vertice
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window))
	{
		//precessa as entradas inseridas na janela em questão
		processInput(window);

		//
		//	comandos de renderização
		//

		//define a cor e renderiza todo o fundo como a cor definida
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//seleciona o programa de shaders usando o objeto de shader da classe shader
        ourShader.use();

		//selecionando a array atual como a VAOs[0]
		glBindVertexArray(VAOs[0]);

		//desenha um triangulo com as informação da array atual 
		//começando pelo valor 0 e possuindo 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//checa e chama eventos e troca os buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//deleta os buffers VAOs e VBOs
	glDeleteVertexArrays(1, VAOs);
	glDeleteBuffers(1, VBOs);

	//deleta o programa de shaders

	//fecha a janela
	glfwTerminate();
	return 0;
}


//função que monitora quando a janela é redimencionada e redimensiona o tamanho da renderização
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//função que processa as entradas do teclando quando manipula a janela em questão
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
