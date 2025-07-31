/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_FEATURE_CONFIG_XML_PARSER_BASE_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_FEATURE_CONFIG_XML_PARSER_BASE_H

#include <string>

#include <libxml/parser.h>
#include <libxml/tree.h>

namespace OHOS::Ace {
enum ParseErrCode {
    PARSE_ERROR = -1,
    PARSE_EXEC_SUCCESS = 0,
    PARSE_NULL_PTR,
    PARSE_XML_NAME_ERROR,
    PARSE_TYPE_ERROR,
    PARSE_SIZE_ERROR,
    PARSE_NO_PARAM,
    PARSE_SYS_FILE_LOAD_FAIL,
    PARSE_PROD_FILE_LOAD_FAIL,
    PARSE_GET_ROOT_FAIL,
    PARSE_GET_CHILD_FAIL,
};

class ConfigXMLParserBase {
public:
    virtual ~ConfigXMLParserBase();

    virtual ParseErrCode ParseFeatureParam(xmlNode& node)
    {
        return PARSE_NO_PARAM;
    }

protected:
    std::string ExtractPropertyValue(const std::string& propName, xmlNode& node);

private:
    void Destroy();
    ParseErrCode LoadPerformanceConfigXML();
    ParseErrCode ParsePerformanceConfigXMLWithBundleName(const std::string& bundleName);
    ParseErrCode ParseXmlNodeNameWithIndex(xmlNode& node, uint32_t nodeNameIndex);
    ParseErrCode ParseInternalWithBundleName(xmlNode& node, const std::string& bundleName);
    void ParseFeatures(xmlNode& node);

    xmlDoc* xmlSysDocument_ = nullptr;

    friend class FeatureParamManager;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_FEATURE_CONFIG_CONFIG_XML_PARSER_BASE_H
