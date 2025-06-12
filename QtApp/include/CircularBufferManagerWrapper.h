#ifndef CIRCULARBUFFERMANAGERWRAPPER_H
#define CIRCULARBUFFERMANAGERWRAPPER_H

#include <QObject>
#include <QDir>
#include <QTimer>

class CircularBufferManagerWrapper : public QObject {
    Q_OBJECT

    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(double rpm READ rpm WRITE setRPM NOTIFY rpmChanged)
    Q_PROPERTY(double fuel READ fuel WRITE setFuel NOTIFY fuelChanged)
    Q_PROPERTY(double voltage READ voltage WRITE setVoltage NOTIFY voltageChanged)
    Q_PROPERTY(double coolanttemp READ coolanttemp WRITE setCoolanttemp NOTIFY coolanttempChanged)
    Q_PROPERTY(double clock READ clock WRITE setClock NOTIFY clockChanged)
    Q_PROPERTY(double enginetemp READ enginetemp WRITE setEnginetemp NOTIFY enginetempChanged)
    Q_PROPERTY(double oiltemp READ oiltemp WRITE setOilTemp NOTIFY oilTempChanged)

    Q_PROPERTY(double gearshift READ gearshift WRITE setGearShift NOTIFY gearshiftChanged)

    Q_PROPERTY(double seatbelt READ seatbelt WRITE setSeatBelt NOTIFY seatbeltChanged)
    Q_PROPERTY(double highlights READ highlights WRITE setHighlights NOTIFY highlightsChanged)
    Q_PROPERTY(double abs READ abs WRITE setABS NOTIFY absChanged)
    Q_PROPERTY(double enginecheck READ enginecheck WRITE setEngineCheck NOTIFY enginecheckChanged)
    Q_PROPERTY(double parking READ parking WRITE setParking NOTIFY parkingChanged)

public:
    explicit CircularBufferManagerWrapper(QObject *parent = nullptr);

    double speed() const;
    double rpm() const;
    double fuel() const;
    double voltage() const;
    double coolanttemp() const;
    double clock() const;
    double enginetemp() const;
    double oiltemp() const;

    double gearshift() const;

    double seatbelt() const;
    double highlights() const;
    double abs() const;
    double enginecheck() const;
    double parking() const;


    void setSpeed(double newSpeed);
    void setRPM(double newRPM);
    void setFuel(double newFuel);
    void setVoltage(double newVoltage);
    void setCoolanttemp(double newCoolanttemp);
    void setClock(double newClock);
    void setEnginetemp(double newEnginetemp);
    void setOilTemp(double newOilTemp);

    void setGearShift(double newGearShift);

    void setSeatBelt(double newSeatBelt);
    void setHighlights(double newHighlights);
    void setABS(double newABS);
    void setEngineCheck(double newEngineCheck);
    void setParking(double newParking);

signals:
    void speedChanged();
    void rpmChanged();
    void fuelChanged();
    void voltageChanged();
    void coolanttempChanged();
    void clockChanged();
    void enginetempChanged();
    void oilTempChanged();

    void gearshiftChanged();

    void seatbeltChanged();
    void highlightsChanged();
    void absChanged();
    void enginecheckChanged();
    void parkingChanged();

private:
    double m_speed;
    double m_rpm;
    double m_fuel;
    double m_voltage;
    double m_coolanttemp;
    double m_clock;
    double m_enginetemp;
    double m_oiltemp;

    double m_gearshift;

    double m_seatbelt;
    double m_highlights;
    double m_abs;
    double m_enginecheck;
    double m_parking;
};

#endif // CIRCULARBUFFERMANAGERWRAPPER_H
