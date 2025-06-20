
import { ManyImportComponent198 } from "./manyImportFile198"
import { ManyImportComponent199 } from "./manyImportFile199"


@Component
export struct ManyImportComponent99 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent198()
            ManyImportComponent199()

        }
    }
}
