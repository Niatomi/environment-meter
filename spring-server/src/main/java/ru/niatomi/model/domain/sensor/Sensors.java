package ru.niatomi.model.domain.sensor;

import lombok.*;

import javax.persistence.*;
import java.time.LocalDateTime;

/**
 * @author niatomi
 */
@Entity
@Table
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class Sensors {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;
    private Integer CO2;
    private Double TDS;
    private Double PH;
    private Double environmentTemperature;
    private Double liquidTemperature;
    private LocalDateTime timeOfCheck;

}
