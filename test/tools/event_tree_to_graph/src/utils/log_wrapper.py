#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# Copyright (c) 2024 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

import logging
from logging import handlers


class LogWrapper:
    logger = None

    def __init__(self):
        self.logger = logging.getLogger('log.txt')
        self.logger.setLevel(logging.DEBUG)
        # max 1M
        file_handler = handlers.RotatingFileHandler(filename='log.txt', maxBytes=1 * 1024 * 1024, backupCount=3,
                                                    encoding='utf-8')
        format_str = logging.Formatter('%(asctime)s - %(levelname)s: %(message)s')
        file_handler.setFormatter(format_str)
        self.logger.addHandler(file_handler)
        console_handler = logging.StreamHandler()
        console_handler.setFormatter(format_str)
        self.logger.addHandler(console_handler)


logWrapper = LogWrapper()
log_debug_enabled = False


def enable_debug(flag):
    global log_debug_enabled
    log_debug_enabled = flag


def log_debug(msg):
    if log_debug_enabled:
        logWrapper.logger.debug(msg)


def log_info(msg):
    if log_debug_enabled:
        logWrapper.logger.info(msg)


def log_warning(msg):
    logWrapper.logger.warning(msg)


def log_error(msg):
    logWrapper.logger.error(msg)


def log_critical(msg):
    logWrapper.logger.critical(msg)


def log_message(msg):
    logWrapper.logger.info(msg)