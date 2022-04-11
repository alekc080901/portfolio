package ru.second.annotationConfig;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.PropertySource;

@Configuration
@ComponentScan("ru.second.annotationConfig")
@PropertySource("classpath:database.properties")
public class SpringConfiguration {

    @Bean
    public Shovel shovel() {
        return Shovel.getShovel();
    }
}
