;; Auto-generated. Do not edit!


(when (boundp 'ZL_B00::pdo_tx_msgs)
  (if (not (find-package "ZL_B00"))
    (make-package "ZL_B00"))
  (shadow 'pdo_tx_msgs (find-package "ZL_B00")))
(unless (find-package "ZL_B00::PDO_TX_MSGS")
  (make-package "ZL_B00::PDO_TX_MSGS"))

(in-package "ROS")
;;//! \htmlinclude pdo_tx_msgs.msg.html


(defclass ZL_B00::pdo_tx_msgs
  :super ros::object
  :slots (_traction_position _traction_velocity _steer_position _steer_velocity ))

(defmethod ZL_B00::pdo_tx_msgs
  (:init
   (&key
    ((:traction_position __traction_position) 0)
    ((:traction_velocity __traction_velocity) 0)
    ((:steer_position __steer_position) 0)
    ((:steer_velocity __steer_velocity) 0)
    )
   (send-super :init)
   (setq _traction_position (round __traction_position))
   (setq _traction_velocity (round __traction_velocity))
   (setq _steer_position (round __steer_position))
   (setq _steer_velocity (round __steer_velocity))
   self)
  (:traction_position
   (&optional __traction_position)
   (if __traction_position (setq _traction_position __traction_position)) _traction_position)
  (:traction_velocity
   (&optional __traction_velocity)
   (if __traction_velocity (setq _traction_velocity __traction_velocity)) _traction_velocity)
  (:steer_position
   (&optional __steer_position)
   (if __steer_position (setq _steer_position __steer_position)) _steer_position)
  (:steer_velocity
   (&optional __steer_velocity)
   (if __steer_velocity (setq _steer_velocity __steer_velocity)) _steer_velocity)
  (:serialization-length
   ()
   (+
    ;; int32 _traction_position
    4
    ;; int32 _traction_velocity
    4
    ;; int32 _steer_position
    4
    ;; int32 _steer_velocity
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _traction_position
       (write-long _traction_position s)
     ;; int32 _traction_velocity
       (write-long _traction_velocity s)
     ;; int32 _steer_position
       (write-long _steer_position s)
     ;; int32 _steer_velocity
       (write-long _steer_velocity s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _traction_position
     (setq _traction_position (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _traction_velocity
     (setq _traction_velocity (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _steer_position
     (setq _steer_position (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _steer_velocity
     (setq _steer_velocity (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get ZL_B00::pdo_tx_msgs :md5sum-) "4311f381460c7d703b7fe50387d84cb7")
(setf (get ZL_B00::pdo_tx_msgs :datatype-) "ZL_B00/pdo_tx_msgs")
(setf (get ZL_B00::pdo_tx_msgs :definition-)
      "int32 traction_position
int32 traction_velocity
int32 steer_position
int32 steer_velocity
")



(provide :ZL_B00/pdo_tx_msgs "4311f381460c7d703b7fe50387d84cb7")


