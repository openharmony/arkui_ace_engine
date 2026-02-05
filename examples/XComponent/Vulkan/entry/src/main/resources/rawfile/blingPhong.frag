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

layout (location = 0) in vec3 fragNormal;
layout (location = 1) in vec3 fragTangent;
layout (location = 2) in float shiness;
layout (location = 3) in vec4 viewDir;
layout (location = 4) in vec4 lightDir;
layout (location = 5) in vec3 lightColor;
layout (location = 6) in vec3 ambi;
layout (location = 7) in vec3 diffuse;
layout (location = 8) in vec3 spec;
layout(location = 0) out vec4 outColor;

void main() {
    float pi = 3.1415927;
    vec3 halfVert = normalize(normalize(lightDir.xyz) + normalize(viewDir.xyz));
    float Lambert = max(0, dot(normalize(lightDir.xyz), normalize(fragNormal)));
    vec3 ambientColor = ambi;
    vec3 diffuseColor = lightColor * 1/pi  * diffuse * Lambert;
    vec3 specularColor = lightColor * spec * max(0, pow(dot(halfVert, normalize(fragNormal)), shiness));
    vec3 color = ambientColor + diffuseColor + specularColor;
    color.x = clamp(color.x, 0.0, 1.0);
    color.y = clamp(color.y, 0.0, 1.0);
    color.z = clamp(color.z, 0.0, 1.0);

    outColor = vec4(color, 1.0);
}
