import path from "path"
import fs from "fs"
import process from "process"
import JSON5 from 'json5'

const CWD = process.cwd()

export class Project {

    moduleJsonPath = path.join(CWD, "entry/src/main/module.json5")
    buildProfilePath = path.join(CWD, "build-profile.json5")
    ohPackageJsonPath = path.join(CWD, "oh-package.json5")

    constructor() {
        this.moduleJson = JSON5.parse(fs.readFileSync(this.moduleJsonPath))
        this.buildProfile = JSON5.parse(fs.readFileSync(this.buildProfilePath))
        this.ohPackageJson = JSON5.parse(fs.readFileSync(this.ohPackageJsonPath))
    }

    getSdkVersion() {
        return this.buildProfile.app.products[0].compileSdkVersion
    }

    addDependency(dep) {
        this.ohPackageJson.dependencies = dep
        fs.writeFileSync(this.ohPackageJsonPath, JSON5.stringify(this.ohPackageJson, null, 4), 'utf-8')
    }

    addDevDependency(dep) {
        this.ohPackageJson.devDependencies = dep
        fs.writeFileSync(this.ohPackageJsonPath, JSON5.stringify(this.ohPackageJson, null, 4), 'utf-8')
    }

    addMetadata(metadata) {
        this.moduleJson.module.metadata = metadata
        fs.writeFileSync(this.moduleJsonPath, JSON5.stringify(this.moduleJson, null, 4), 'utf-8')
    }

    addMetadataOptions(options) {
        if (!this.moduleJson.module.metadata) {
            this.addMetadata([])
        }
        this.moduleJson.module.metadata.push(options)
        fs.writeFileSync(this.moduleJsonPath, JSON5.stringify(this.moduleJson, null, 4), 'utf-8')
    }

}