#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

//	prototipagens
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//	codigos dos shaders

//shader do vertices do objeto
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);"
"}\0";

//shader de fragmento de cor
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"
"}\0";

int main()
{
	//inicia o glfw
	glfwInit();

	//configura a vers�o do opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//	caso seja para um sistema MacOs essa linha deve ser inserida
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPACT, GL_TRUE);

	//declara��o da janela
	GLFWwindow* window = glfwCreateWindow(800, 600, "Glfw window", NULL, NULL);

	//mensagem de erro caso a janela n�o seja criada
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

	//fu��o que muda o tamanho da render de acordo com a janela
	//toda vez que ela for redimencionada
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//declara��p dos vertices do nosso objeto em uma array de float
	
	//vertices do triangulo
	float triangle[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	//declara��o de variaveis que seram usadas no log
	int success;
	char infoLog[512];

	//declara��o de dois VBOs(Vertex Buffer Object)
	unsigned int VBOs[1];
	glGenBuffers(1, VBOs);

	//declara��o de duas VAOs(Vertex Array Object)
	unsigned int VAOs[1];
	glGenVertexArrays(1, VAOs);

	//selecionando a array atual como a VAO[0]
	glBindVertexArray(VAOs[0]);

	//ligando o objeto de vertice VBOs[0] ao objeto de array atual(VAO[0])
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

	//definindo os dados do VBOs[0] com os vertices do triangle_one e definindo seu tipo
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	
	//definindo o tipo e o tamanho de cada vertice na memoria do VAOs[0]
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//declarando o objeto do shader dos vertices
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//ligando o codigo fonte do shader de vertices
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	//compilando o shader de vertice
	glCompileShader(vertexShader);

	//gera uma mensagem de erro caso a compila��o do shader de errado
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//declarando o shader de fragmento
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//ligando o codigo fonte do shader de fragmento
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	//compilando o shader de fragmento
	glCompileShader(fragmentShader);

	//gera uma mensagem de erro caso a compila��o do shader de errado
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//declarando programas de shaders
	unsigned int shaderProgram;

	//criando o programa do shader
	shaderProgram = glCreateProgram();

	//adicionando os shaders criados ao programa de shader
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//ligando os shaders ao programa de shader
	glLinkProgram(shaderProgram);

	//gera uma mensagem de erro caso a liga��o de errado
	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//deleta os shaders de vertices e de fragmentos apos a liga��o deles ao programa
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//loop de renderiza��o
	while (!glfwWindowShouldClose(window))
	{
		//precessa as entradas inseridas na janela em quest�o
		processInput(window);

		//	comandos de renderiza��o

		//define a cor e renderiza todo o fundo como a cor definida
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//seleciona o programa de shaders
		glUseProgram(shaderProgram);

		//selecionando a array atual como a VAOs[0]
		glBindVertexArray(VAOs[0]);

		//desenha um triangulo com as informa��o da array atual 
		//come�ando pelo valor 0 e possuindo 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//checa e chama eventos e troca os buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//deleta os buffers VAOs e VBOs
	glDeleteVertexArrays(1, VAOs);
	glDeleteBuffers(1, VBOs);

	//deleta o programa de shaders
	glDeleteProgram(shaderProgram);

	//fecha a janela
	glfwTerminate();
	return 0;
}


//fun��o que monitora quando a janela � redimencionada e redimensiona o tamanho da renderiza��o
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//fun��o que processa as entradas do teclando quando manipula a janela em quest�o
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
