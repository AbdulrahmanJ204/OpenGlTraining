#pragma once

#include "Light.h"

class PointLight : public Light {
public:
    PointLight(const glm::vec3& position,
        const glm::vec3& ambient,
        const glm::vec3& diffuse,
        const glm::vec3& specular,
        float constant, float linear, float quadratic) {
        this->position = position;
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->constant = constant;
        this->linear = linear;
        this->quadratic = quadratic;
    }

    void uploadToShader(Shader& shader, const std::string& uniformName) const override {
        shader.SetUniform3fv(uniformName + ".position", position);
        shader.SetUniform3fv(uniformName + ".ambient", ambient);
        shader.SetUniform3fv(uniformName + ".diffuse", diffuse);
        shader.SetUniform3fv(uniformName + ".specular", specular);
        shader.SetUniform1f(uniformName + ".constant", constant);
        shader.SetUniform1f(uniformName + ".linear", linear);
        shader.SetUniform1f(uniformName + ".quadratic", quadratic);
    }

private:
    glm::vec3 position;
    float constant, linear, quadratic;
};
