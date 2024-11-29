#pragma once

#include "Light.h"

class SpotLight : public Light {
public:
    SpotLight(const glm::vec3& position, const glm::vec3& direction,
              const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
              float constant, float linear, float quadratic,
              float cutOff, float outerCutOff) {
        this->position = position;
        this->direction = direction;
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->constant = constant;
        this->linear = linear;
        this->quadratic = quadratic;
        this->cutOff = glm::cos(glm::radians(cutOff));
        this->outerCutOff = glm::cos(glm::radians(outerCutOff));
    }

    void uploadToShader(Shader& shader, const std::string& uniformName) const override {
        shader.SetUniform3fv(uniformName + ".position", position);
        shader.SetUniform3fv(uniformName + ".direction", direction);
        shader.SetUniform3fv(uniformName + ".ambient", ambient);
        shader.SetUniform3fv(uniformName + ".diffuse", diffuse);
        shader.SetUniform3fv(uniformName + ".specular", specular);
        shader.SetUniform1f(uniformName + ".constant", constant);
        shader.SetUniform1f(uniformName + ".linear", linear);
        shader.SetUniform1f(uniformName + ".quadratic", quadratic);
        shader.SetUniform1f(uniformName + ".cutOff", cutOff);
        shader.SetUniform1f(uniformName + ".outerCutOff", outerCutOff);
    }

private:
    glm::vec3 position;
    glm::vec3 direction;
    float constant, linear, quadratic;
    float cutOff, outerCutOff;
};
