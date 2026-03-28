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

/**
 * RenderId Generator - generates unique incrementing IDs for SurfaceController instances
 */
export class RenderIdGenerator {
    private static instance: RenderIdGenerator | null = null;
    private nextId: number = 0;

    private constructor() {
        // Private constructor for singleton pattern
    }

    /**
     * Get the singleton instance of RenderIdGenerator
     */
    public static getInstance(): RenderIdGenerator {
        if (RenderIdGenerator.instance === null) {
            RenderIdGenerator.instance = new RenderIdGenerator();
        }
        return RenderIdGenerator.instance;
    }

    /**
     * Generate a new unique render ID
     * @returns A new unique render ID
     */
    public generateId(): number {
        const id = this.nextId;
        this.nextId++;
        return id;
    }

    /**
     * Reset the generator (mainly for testing purposes)
     */
    public reset(): void {
        this.nextId = 0;
    }

    /**
     * Get the current next ID without incrementing
     * @returns The next ID that will be generated
     */
    public peekNextId(): number {
        return this.nextId;
    }
}
