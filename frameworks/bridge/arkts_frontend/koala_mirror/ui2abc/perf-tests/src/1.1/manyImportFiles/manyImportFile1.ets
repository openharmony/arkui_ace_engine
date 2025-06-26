
import { ManyImportComponent2 } from "./manyImportFile2"
import { ManyImportComponent3 } from "./manyImportFile3"


@Component
export struct ManyImportComponent1 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent2()
            ManyImportComponent3()

        }
    }
}
