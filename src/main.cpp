#include "../glad/include/glad/glad.h"
#include "../glfw/include/glfw/glfw3.h"
#include <iostream>

//	prototipagens
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//	codigos dos shaders

//shader do vertices do objeto
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

//shader de fragmento de cor
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\0";

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

	//declaração dos vertices do nosso objeto em uma array de float
	
	//vertices do triangulo
	float triangle[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//declarando o objeto do shader dos vertices
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//ligando o codigo fonte do shader de vertices
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	//compilando o shader de vertice
	glCompileShader(vertexShader);

	//gera uma mensagem de erro caso a compilação do shader de errado
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

	//gera uma mensagem de erro caso a compilação do shader de errado
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

	//gera uma mensagem de erro caso a ligação de errado
	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//deleta os shaders de vertices e de fragmentos apos a ligação deles ao programa
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//loop de renderização
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

		//variavel com valor dada por uma função que pega o valor do tempo
		float timeValue = glfwGetTime();

		//variavel variavel que muda seu valor entre 0.0f e 1.0f enquanto o tempo passa
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

		//variavel que armazena o local aonde a variavel uniform com o nome ourColor está
		//dentro do programa de shaders
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		//seleciona o programa de shaders
		glUseProgram(shaderProgram);

		//função que atribui 4 valores de ponto flutuante a variavel selecionada.
		//no caso a variavel vertexColorLocation guarda o local da variavel ourColor, e
		//ourColor é do tipo vec4 e precisa de 4 valores do tipo float.
		//a variavel greenValue esta no lugar do valor verde muda constantemente ao passar
		//do tempo.
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

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
	glDeleteProgram(shaderProgram);

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
