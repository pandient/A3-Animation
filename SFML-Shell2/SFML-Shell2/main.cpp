#include <GL\glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>
#include "Shader.h"
#include "Bone.h"


GLuint VBO;


static const char* pVS = "                                                    \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 Position;                                       \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0);  \n\
}";

static const char* pFS = "                                                    \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 FragColor;                                                           \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);                                     \n\
}";

int main(int argc, char** argv)
{
    // Request a 32-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 32;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML graphics with OpenGL", sf::Style::Default, contextSettings);
    window.setVerticalSyncEnabled(true);

    // Make it the active window for OpenGL calls
    window.setActive();

    // Create some text to draw on top of our OpenGL object
    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf"))
        return EXIT_FAILURE;
    sf::Text text("SFML / OpenGL demo", font);
    text.setColor(sf::Color(255, 255, 255, 170));
    text.setPosition(250.f, 450.f);



    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

  
    // Configure the viewport (the same size as the window)
    glViewport(0, 0, window.getSize().x, window.getSize().y);

    //// Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);
	/*glMatrixMode(GL_PROJECTION);
 	glOrtho(-200, 200, -200, 200, -5, 5);
 	glMatrixMode(GL_MODELVIEW);*/
   
    sf::Clock clock;

	
	//sf::Vector3f Vertices[4];
 //   Vertices[0] = sf::Vector3f(-1.0f, -1.0f, 0.0f);
 //   Vertices[1] = sf::Vector3f(1.0f, -1.0f, 0.0f);
 //   Vertices[2] = sf::Vector3f(0.0f, 1.0f, 0.0f);
	//Vertices[3] = sf::Vector3f(1.0f, 1.0f, 0.0f);

 //	glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	
	Bone* b1 = new Bone(0.0 , 0.0 , 0.0,1.0, NULL);


	Shader* shader = new Shader();
	shader->CompileShaders();

    // Start game loop
    while (window.isOpen())
    {
		
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Escape key : exit
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
			

            // Adjust the viewport when the window is resized
            if (event.type == sf::Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);
        }

		
		
      //   Clear the depth buffer
        glClear(GL_DEPTH_BUFFER_BIT);
		
/*		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_QUADS, 0, 4);
		glDisableVertexAttribArray(0)*/;
		b1->Draw();

        //// Draw some text on top of our OpenGL object
        //window.pushGLStates();
        //window.draw(text);
        //window.popGLStates();

        // Finally, display the rendered frame on screen
        window.display();
    }


    return EXIT_SUCCESS;
}