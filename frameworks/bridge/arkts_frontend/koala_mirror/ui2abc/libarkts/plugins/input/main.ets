import { Component } from "./library"

@interface BuilderLambda {
	value: string
}

@Component
struct MyComponent {
	@BuilderLambda("MyComponent.instantiateImpl")
	static $_instantiate(factory: () => MyComponent): MyComponent {
		const instance = factory()
		return instance
	}

	static instantiateImpl(builder: (instance: MyComponent)=>void, factory: () => MyComponent): void {
		const instance = factory()
		builder(instance)
	}

	width(value: number): MyComponent { return this }
	build() {}
}


@Component
struct AnotherComponent {

	build() {
		MyComponent()
			.width(17.0)
	}
}
