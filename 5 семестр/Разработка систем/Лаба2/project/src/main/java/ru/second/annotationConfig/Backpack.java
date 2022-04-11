package ru.second.annotationConfig;

import lombok.Data;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;

@Component
public @Data
class Backpack {
    private final String brandName;
    private Portable burden;

    @PostConstruct
    public void init() {
        System.out.println("Создание бина рюкзака.");
    }

    @Autowired
    public Backpack(@Qualifier("shovel") Portable burden,
                    @Value("${backpack.brandName}") String brandName) {
        this.burden = burden;
        this.brandName = brandName;
    }

    @PreDestroy
    public void destroy() {
        System.out.println("Бин рюкзака уничтожен");
    }
}
