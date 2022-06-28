package ru.niatomi.model.domain.schedule;

import lombok.*;

import javax.persistence.*;
import java.time.LocalDateTime;

/**
 * @author niatomi
 */
@Entity
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class Schedule {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    private LocalDateTime checkDateTime;

}
