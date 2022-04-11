package ru.nikitin.server.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import ru.nikitin.server.services.UserService;

@Controller
@RequestMapping("/account")
class RegisterController {
    private final PasswordEncoder passwordEncoder;
    private final UserService userService;

    @Autowired
    public RegisterController(@Qualifier("passwordEncoder") PasswordEncoder passwordEncoder,
                              @Qualifier("userServiceImpl") UserService userService) {
        this.passwordEncoder = passwordEncoder;
        this.userService = userService;
    }

    @GetMapping("/register")
    public String register() {
        return "registration";
    }

    @PostMapping("/register")
    public String registerHandler(@RequestParam String username, @RequestParam String password) {
        try {
            boolean registerSuccess = userService.register(username, passwordEncoder.encode(password));
            if (registerSuccess)
                System.out.println("Создан пользователь " + username);
            else {
                System.out.println("Существует пользователь " + username);
                return "registration";
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return "redirect:/account/auth";
    }

    @GetMapping("/auth")
    public String auth() {
        return "auth";
    }
}
