/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Retention({policy: "SOURCE"})
export @interface BuilderLambda {
    name: string
}

@Retention({policy: "SOURCE"})
export @interface ComponentBuilder {}

@Retention({policy: "SOURCE"})
export @interface Entry {}

@Retention({policy: "SOURCE"})
export @interface Component {}

@Retention({policy: "SOURCE"})
export @interface State {}

@Retention({policy: "SOURCE"})
export @interface Builder {}

@Retention({policy: "SOURCE"})
export @interface Link {}

@Retention({policy: "SOURCE"})
export @interface Prop {}

@Retention({policy: "SOURCE"})
export @interface Provide {}

@Retention({policy: "SOURCE"})
export @interface Consume {}

/**
 * Component lifecycle decorator for component initialization
 * Marks a method to be called when component is initialized
 */
@Retention({policy: "SOURCE"})
export @interface ComponentInit {}

/**
 * Component lifecycle decorator for component appearance
 * Marks a method to be called when component is about to appear
 */
@Retention({policy: "SOURCE"})
export @interface ComponentAppear {}

/**
 * Component lifecycle decorator for component build completion
 * Marks a method to be called after component has been built
 */
@Retention({policy: "SOURCE"})
export @interface ComponentBuilt {}

/**
 * Component lifecycle decorator for component disappearance
 * Marks a method to be called when component is about to disappear
 */
@Retention({policy: "SOURCE"})
export @interface ComponentDisappear {}

/**
 * Component lifecycle decorator for component reuse
 * Marks a method to be called when component is about to be reused
 */
@Retention({policy: "SOURCE"})
export @interface ComponentReuse {}

/**
 * Component lifecycle decorator for component recycling
 * Marks a method to be called when component is about to be recycled
 */
@Retention({policy: "SOURCE"})
export @interface ComponentRecycle {}