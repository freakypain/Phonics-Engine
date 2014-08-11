#include <iostream>
#include "Spotlight.hpp"
#include "../Light.hpp"
#include "../GameObject.hpp"
#include "../Renderer.hpp"
#include "../ShaderProgram.hpp"



Spotlight::Spotlight(GameObject * aParent ) : Light(aParent)
{

}

Spotlight::~Spotlight()
{

}

void Spotlight::draw(Renderer * aRenderer, glm::mat4 aParentTransform)
{

    //std::cout << "Draw Spot Light: " <<  aRenderer->getShaderProgram()->id << std::endl;


    aRenderer->getShaderProgram()->setUniform("material_ambient", 0.2f, 0.2f, 0.2f, 1.0f);
    aRenderer->getShaderProgram()->setUniform("material_diffuse", 0.0f, 1.0f, 0.3f, 1.0f);
    aRenderer->getShaderProgram()->setUniform("material_specular", 1.0f, 1.0f, 0.0f, 1.0f);
    aRenderer->getShaderProgram()->setUniform("material_emissive", 0.3f, 0.3f, 0.3f, 1.0f);

    aRenderer->getShaderProgram()->setUniform("material_shininess", 15.0f);

    // Set uniforms
    if(parent->getName() == "PointLight1"){

        aRenderer->getShaderProgram()->setUniform("texture0", 0);

        aRenderer->getShaderProgram()->setUniform("light[0].ambient", 0.0f, 0.0f, 0.0f, 1.0f);
        aRenderer->getShaderProgram()->setUniform("light[0].diffuse", 1.0f, 1.0f, 1.0f, 1.0f);
        aRenderer->getShaderProgram()->setUniform("light[0].specular", 1.0f, 1.0f, 0.0f, 1.0f);
        aRenderer->getShaderProgram()->setUniform("light[0].constant_attenuation", 0.5f);
        aRenderer->getShaderProgram()->setUniform("light[0].linear_attenuation", 0.1f);
        aRenderer->getShaderProgram()->setUniform("light[0].quadratic_attenuation", 0.05f);

        aRenderer->getShaderProgram()->setUniform("light[0].position", parent->getLocation()[0] , parent->getLocation()[1], parent->getLocation()[2], 1.0f);

    }else{
        aRenderer->getShaderProgram()->setUniform("texture0", 0);


        aRenderer->getShaderProgram()->setUniform("material_ambient", 0.2f, 0.2f, 0.2f, 1.0f);
        aRenderer->getShaderProgram()->setUniform("material_diffuse", 1.0f, 0.0f, 0.0f, 1.0f);
        aRenderer->getShaderProgram()->setUniform("material_specular", 1.0f, 1.0f, 0.0f, 1.0f);
        aRenderer->getShaderProgram()->setUniform("material_emissive", 0.0f, 0.0f, 0.0f, 1.0f);

        aRenderer->getShaderProgram()->setUniform("material_shininess", 15.0f);

        aRenderer->getShaderProgram()->setUniform("light[1].ambient", 0.0f, 0.0f, 0.0f, 1.0f);
        aRenderer->getShaderProgram()->setUniform("light[1].diffuse", 5.0f, 0.0f, 0.0f, 1.0f);
        aRenderer->getShaderProgram()->setUniform("light[1].specular", 5.0f, 0.0f, 0.0f, 1.0f);
        aRenderer->getShaderProgram()->setUniform("light[1].constant_attenuation", 0.5f);
        aRenderer->getShaderProgram()->setUniform("light[1].linear_attenuation", 0.1f);
        aRenderer->getShaderProgram()->setUniform("light[1].quadratic_attenuation", 0.05f);

        aRenderer->getShaderProgram()->setUniform("light[1].position", parent->getLocation()[0] , parent->getLocation()[1], parent->getLocation()[2], 1.0f);




    }
}

