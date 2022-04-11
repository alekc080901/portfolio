package ru.nikitin.services.impl;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;
import ru.nikitin.entities.UserEntity;
import ru.nikitin.repos.UserRepository;
import ru.nikitin.services.UserService;

@Service("userServiceImpl")
public class UserServiceImpl implements UserDetailsService, UserService {
    @Autowired
    private UserRepository userRepository;

    @Override
    public UserDetails loadUserByUsername(String username)
            throws UsernameNotFoundException {
        UserEntity userEntity = userRepository.findByUsername(username).orElse(null);

        if (userEntity == null) {
            throw new UsernameNotFoundException("Пользователь не найден!");
        }

        return new UserDetailsImpl(userEntity);
    }

    @Override
    public boolean register(String username, String password) {
        if (userRepository.findByUsername(username).isPresent())
            return false;
        UserEntity userEntity = new UserEntity(username, password);
        userRepository.save(userEntity);
        return true;
    }
}
