package ru.nikitin.server.repos;

import org.springframework.data.jpa.repository.JpaRepository;
import ru.nikitin.server.entities.UserEntity;

import java.util.Optional;

public interface UserRepository extends JpaRepository<UserEntity, Integer> {
    Optional<UserEntity> findByUsername(String username);
    Optional<UserEntity> findByUsernameAndPassword(String username, String password);
}
