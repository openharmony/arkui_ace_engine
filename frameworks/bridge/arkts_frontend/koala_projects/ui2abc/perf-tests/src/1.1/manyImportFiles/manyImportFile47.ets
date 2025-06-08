
import { ManyImportComponent94 } from "./manyImportFile94"
import { ManyImportComponent95 } from "./manyImportFile95"


@Component
export struct ManyImportComponent47 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent94()
            ManyImportComponent95()

        }
    }
}
