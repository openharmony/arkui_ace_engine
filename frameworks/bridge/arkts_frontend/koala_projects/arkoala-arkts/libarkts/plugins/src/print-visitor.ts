import * as arkts from "@koalaui/libarkts"
import { AbstractVisitor } from "./AbstractVisitor";

export class PrintVisitor extends AbstractVisitor {
    private result = ""

    private printNode(node: arkts.AstNode) {
        return `${" ".repeat(4 * this.indentation) + node.constructor.name} ${this.nameIfIdentifier(node)}`
    }

    private nameIfIdentifier(node: arkts.AstNode): string {
        return arkts.isIdentifier(node) ? `'${node.name}'` : ""
    }

    visitor(node: arkts.AstNode): arkts.AstNode {
        console.log(this.printNode(node))
        return this.visitEachChild(node)
    }
}
