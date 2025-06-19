/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { request } from 'https'
import { Command } from 'commander'

const program = new Command()

// Define a flag for filtering by platform: linux or windows
program
  .option('-p, --platform <platform>', 'Platform filter (linux or windows)')
  .parse(process.argv)

const options = program.opts()
const platformFilter = options.platform ? options.platform.toLowerCase() : null

const openlabUsername = process.env.OPENLAB_USERNAME
const openlabPassword = process.env.OPENLAB_PASSWORD

if (!openlabUsername || !openlabPassword) {
  console.error('Please set OPENLAB_USERNAME and OPENLAB_PASSWORD environment variables')
  process.exit(1)
}

const requestOptions = {
  hostname: 'nexus.bz-openlab.ru',
  port: 10443,
  path: '/service/rest/v1/search?keyword=Previewer',
  method: 'GET',
  headers: {
    'Authorization': 'Basic ' + Buffer.from(`${openlabUsername}:${openlabPassword}`).toString('base64')
  }
}

const req = request(requestOptions, (response) => {
  let responseData = ''

  response.on('data', (chunk) => {
    responseData += chunk
  })

  response.on('end', () => {
    try {
      const parsedResponse = JSON.parse(responseData)

      // Filtering items by platform, if filter is specified
      let filteredItems = parsedResponse.items
      if (platformFilter) {
        filteredItems = parsedResponse.items.filter(item => {
          const itemNameLowerCase = item.name.toLowerCase()
          if (platformFilter === 'linux') {
            return itemNameLowerCase.includes('linux')
          }
          return itemNameLowerCase.includes('windows')
        })
      }

      // Sorting items by last modified date from oldest to newest
      const sortedItems = filteredItems.sort((a, b) => {
        const dateA = new Date(a.assets[0].lastModified)
        const dateB = new Date(b.assets[0].lastModified)
        return dateA - dateB
      })

      const filterDescription = platformFilter ? ` for ${platformFilter}` : ''
      console.log(`Found ${sortedItems.length} items${filterDescription}, sorted by date (oldest first):\n`)

      sortedItems.forEach(item => {
        const asset = item.assets[0]
        const lastModifiedDate = new Date(asset.lastModified).toLocaleString()
        console.log(`${item.name}\n  Last Modified: ${lastModifiedDate}\n  Size: ${(asset.fileSize / 1024 / 1024).toFixed(2)} MB\n`)
      })

      if (sortedItems.length === 0) {
        console.log(`No items found${filterDescription}`)
      }
    } catch (error) {
      console.error('Error parsing response:', error)
    }
  })
})

req.on('error', (error) => {
  console.error('Error making request:', error)
})

req.end()
