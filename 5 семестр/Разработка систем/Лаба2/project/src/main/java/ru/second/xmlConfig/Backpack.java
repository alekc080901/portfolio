package ru.second.xmlConfig;

import lombok.Data;

public @Data
class Backpack {
    private final String brandName;
    private Portable burden;
}
