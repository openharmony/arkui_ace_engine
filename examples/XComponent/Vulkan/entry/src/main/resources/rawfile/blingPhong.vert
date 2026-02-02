/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#version 450
layout (binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    mat4 inverseView;
} ubo;

layout (binding = 1) uniform UniformLight {
    vec4 lightPos;
    vec4 lightColor;
} light;

layout (binding = 2) uniform UniformMaterial {
    vec4 ambi;
    vec4 diff;
    vec4 spec;
    // float shiness;
} material;

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec2 uv;
layout (location = 0) out vec3 fragNormal;
layout (location = 1) out vec3 fragTangent;
layout (location = 2) out float shiness;
layout (location = 3) out vec4 viewDir;
layout (location = 4) out vec4 lightDir;
layout (location = 5) out vec3 lightColor;
layout (location = 6) out vec3 ambi;
layout (location = 7) out vec3 diff;
layout (location = 8) out vec3 spec;

void main() {
    vec4 worldCoord = ubo.model * vec4(inPosition, 1.0);
    vec4 viewCoord = ubo.view * worldCoord;
    fragNormal = (ubo.model * vec4(normal, 0)).xyz; // no single dir scal
    fragTangent = (ubo.model * vec4(tangent, 0)).xyz;
    shiness = material.spec.w;
    viewDir = ubo.inverseView * vec4(0, 0, 0, 1) - worldCoord;
    lightDir = vec4(light.lightPos - worldCoord);
    lightColor = light.lightColor.xyz;
    // lightColor = vec3(1,1,1);
    ambi = material.ambi.xyz;
    diff = material.diff.xyz;
    spec = material.spec.xyz;
    gl_Position = ubo.proj * viewCoord;
}
