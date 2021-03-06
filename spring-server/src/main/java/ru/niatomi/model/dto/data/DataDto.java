package ru.niatomi.model.dto.data;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.time.LocalDateTime;

/**
 * @author niatomi
 */
@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class DataDto {

    private Integer CO2;
    private Double TDS;
    private Double PH;
    private Double environmentTemperature;
    private Double liquidTemperature;
    private LocalDateTime timeOfCheck;

}
