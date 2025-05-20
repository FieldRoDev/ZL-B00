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
  :slots (_id _data ))

(defmethod ZL_B00::pdo_tx_msgs
  (:init
   (&key
    ((:id __id) 0)
    ((:data __data) (make-array 4 :initial-element 0 :element-type :char))
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _data __data)
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; uint32 _id
    4
    ;; uint8[4] _data
    (* 1    4)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _id
       (write-long _id s)
     ;; uint8[4] _data
     (princ _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _id
     (setq _id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint8[4] _data
   (setq _data (make-array 4 :element-type :char))
   (replace _data buf :start2 ptr-) (incf ptr- 4)
   ;;
   self)
  )

(setf (get ZL_B00::pdo_tx_msgs :md5sum-) "e9771f6fc35a81e831d4a03276869531")
(setf (get ZL_B00::pdo_tx_msgs :datatype-) "ZL_B00/pdo_tx_msgs")
(setf (get ZL_B00::pdo_tx_msgs :definition-)
      "uint32 id
uint8[4] data
")



(provide :ZL_B00/pdo_tx_msgs "e9771f6fc35a81e831d4a03276869531")


