package ru.second.annotationConfig;

import lombok.Data;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;

@Component
public @Data
class Shovel implements Portable {
    @Value("${ru.second.annotationConfig.shovelTypes}")
    private ShovelTypes type;

    @PostConstruct
    public void init() {
        System.out.println("Создание бина лопаты.");
    }

    private Shovel() {
    }

    public static Shovel getShovel() {
        return new Shovel();
    }

    @Override
    public void showInfo() {
        System.out.println("Название объекта: лопата");
        System.out.println("Тип лопаты: " + this.type.name().toLowerCase());
    }

    @PreDestroy
    public void destroy() {
        System.out.println("Бин лопаты уничтожен");
    }
}
