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
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

//shader da cor laranja
const char* fragmentShaderSourceOrange = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

//shader da cor amarela
const char* fragmentShaderSourceYellow = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
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

	//fução que muda o tamanho da render de acordo com a janela
	//toda vez que ela for redimencionada
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//declaraçãp dos vertices do nosso objeto em uma array de float
	
	//vertices do primeiro triangulo
	float triangle_one[] = {
		-0.75f, -0.25f, 0.0f,
		-0.25f, -0.25f, 0.0f,
		-0.5f, 0.25f, 0.0f
	};

	//vertices do secundo triangulo
	float triangle_two[] = {
		0.25f, -0.25f, 0.0f,
		0.75f, -0.25f, 0.0f,
		0.50f, 0.25f, 0.0f
	};

	//declaração de variaveis que seram usadas no log
	int success;
	char infoLog[512];

	//declaração de dois VBOs(Vertex Buffer Object)
	unsigned int VBOs[2];
	glGenBuffers(2, VBOs);

	//declaração de duas VAOs(Vertex Array Object)
	unsigned int VAOs[2];
	glGenVertexArrays(2, VAOs);

	//selecionando a array atual como a VAO[0]
	glBindVertexArray(VAOs[0]);

	//ligando o objeto de vertice VBOs[0] ao objeto de array atual(VAO[0])
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

	//definindo os dados do VBOs[0] com os vertices do triangle_one e definindo seu tipo
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_one), triangle_one, GL_STATIC_DRAW);
	
	//definindo o tipo e o tamanho de cada vertice na memoria do VAOs[0]
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//selecionando a array atual como a VAOs[1]
	glBindVertexArray(VAOs[1]);

	//ligando o objeto de vertice VBOs[1] ao objeto de array atual(VAO[1])
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);

	//definindo os dados do VBOs[1] com os vertices do triangle_two e definindo seu tipo
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_two), triangle_two, GL_STATIC_DRAW);

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

	//gera uma mensagem de erro caso a compilação do shader de errado
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//declarando o shader de framento
	unsigned int fragmentShaderOrange, fragmentShaderYellow;
	fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);

	//ligando o codigo fonte do shader de fragmento
	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);

	//compilando o shader de fragmento
	glCompileShader(fragmentShaderOrange);

	//gera uma mensagem de erro caso a compilação do shader de errado
	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);

	//ligando o codigo fonte do shader de fragmento
	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);

	//compilando o shader de fragmento
	glCompileShader(fragmentShaderYellow);

	//gera uma mensagem de erro caso a compilação do shader de errado
	glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//declarando programas de shaders
	unsigned int shaderProgramOrange, shaderProgramYellow;

	//criando o programa do shader laranja
	shaderProgramOrange = glCreateProgram();

	//adicionando os shaders criados ao programa de shader laranja
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);

	//ligando os shaders ao programa de shader laranja
	glLinkProgram(shaderProgramOrange);

	//gera uma mensagem de erro caso a ligação de errado
	glGetShaderiv(shaderProgramOrange, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgramOrange, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//criando o programa do shader amarelo
	shaderProgramYellow = glCreateProgram();

	//adicionando os shaders criados ao programa de shader amarelo
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);

	//ligando os shaders ao programa de shader amarelo
	glLinkProgram(shaderProgramYellow);

	//gera uma mensagem de erro caso a ligação de errado
	glGetShaderiv(shaderProgramYellow, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgramYellow, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//deleta os shaders de vertices e de fragmentos apos a ligação deles ao programa
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderOrange);
	glDeleteShader(fragmentShaderYellow);

	//loop de renderização
	while (!glfwWindowShouldClose(window))
	{
		//precessa as entradas inseridas na janela em questão
		processInput(window);

		//	comandos de renderização

		//define a cor e renderiza todo o fundo como a cor definida
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//seleciona o programa de shaders com a cor laranja
		glUseProgram(shaderProgramOrange);

		//selecionando a array atual como a VAOs[0]
		glBindVertexArray(VAOs[0]);

		//desenha um triangulo com as informação da array atual 
		//começando pelo valor 0 e possuindo 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);


		//seleciona o programa de shaders com a cor amarela
		glUseProgram(shaderProgramYellow);
		
		//selecionando a array atual como a VAOs[1]
		glBindVertexArray(VAOs[1]);

		//desenha um triangulo com as informação da array atual 
		//começando pelo valor 0 e possuindo 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);
		

		//checa e chama eventos e troca os buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//deleta os buffers VAOs e VBOs
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	//deleta o programa de shaders
	glDeleteProgram(shaderProgramOrange);
	glDeleteProgram(shaderProgramYellow);

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