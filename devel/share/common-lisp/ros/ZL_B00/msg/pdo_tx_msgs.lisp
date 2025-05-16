; Auto-generated. Do not edit!


(cl:in-package ZL_B00-msg)


;//! \htmlinclude pdo_tx_msgs.msg.html

(cl:defclass <pdo_tx_msgs> (roslisp-msg-protocol:ros-message)
  ((traction_position
    :reader traction_position
    :initarg :traction_position
    :type cl:integer
    :initform 0)
   (traction_velocity
    :reader traction_velocity
    :initarg :traction_velocity
    :type cl:integer
    :initform 0)
   (steer_position
    :reader steer_position
    :initarg :steer_position
    :type cl:integer
    :initform 0)
   (steer_velocity
    :reader steer_velocity
    :initarg :steer_velocity
    :type cl:integer
    :initform 0))
)

(cl:defclass pdo_tx_msgs (<pdo_tx_msgs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pdo_tx_msgs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pdo_tx_msgs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ZL_B00-msg:<pdo_tx_msgs> is deprecated: use ZL_B00-msg:pdo_tx_msgs instead.")))

(cl:ensure-generic-function 'traction_position-val :lambda-list '(m))
(cl:defmethod traction_position-val ((m <pdo_tx_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ZL_B00-msg:traction_position-val is deprecated.  Use ZL_B00-msg:traction_position instead.")
  (traction_position m))

(cl:ensure-generic-function 'traction_velocity-val :lambda-list '(m))
(cl:defmethod traction_velocity-val ((m <pdo_tx_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ZL_B00-msg:traction_velocity-val is deprecated.  Use ZL_B00-msg:traction_velocity instead.")
  (traction_velocity m))

(cl:ensure-generic-function 'steer_position-val :lambda-list '(m))
(cl:defmethod steer_position-val ((m <pdo_tx_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ZL_B00-msg:steer_position-val is deprecated.  Use ZL_B00-msg:steer_position instead.")
  (steer_position m))

(cl:ensure-generic-function 'steer_velocity-val :lambda-list '(m))
(cl:defmethod steer_velocity-val ((m <pdo_tx_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ZL_B00-msg:steer_velocity-val is deprecated.  Use ZL_B00-msg:steer_velocity instead.")
  (steer_velocity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pdo_tx_msgs>) ostream)
  "Serializes a message object of type '<pdo_tx_msgs>"
  (cl:let* ((signed (cl:slot-value msg 'traction_position)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'traction_velocity)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'steer_position)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'steer_velocity)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pdo_tx_msgs>) istream)
  "Deserializes a message object of type '<pdo_tx_msgs>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'traction_position) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'traction_velocity) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'steer_position) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'steer_velocity) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<pdo_tx_msgs>)))
  "Returns string type for a message object of type '<pdo_tx_msgs>"
  "ZL_B00/pdo_tx_msgs")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pdo_tx_msgs)))
  "Returns string type for a message object of type 'pdo_tx_msgs"
  "ZL_B00/pdo_tx_msgs")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<pdo_tx_msgs>)))
  "Returns md5sum for a message object of type '<pdo_tx_msgs>"
  "4311f381460c7d703b7fe50387d84cb7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pdo_tx_msgs)))
  "Returns md5sum for a message object of type 'pdo_tx_msgs"
  "4311f381460c7d703b7fe50387d84cb7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pdo_tx_msgs>)))
  "Returns full string definition for message of type '<pdo_tx_msgs>"
  (cl:format cl:nil "int32 traction_position~%int32 traction_velocity~%int32 steer_position~%int32 steer_velocity~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pdo_tx_msgs)))
  "Returns full string definition for message of type 'pdo_tx_msgs"
  (cl:format cl:nil "int32 traction_position~%int32 traction_velocity~%int32 steer_position~%int32 steer_velocity~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pdo_tx_msgs>))
  (cl:+ 0
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pdo_tx_msgs>))
  "Converts a ROS message object to a list"
  (cl:list 'pdo_tx_msgs
    (cl:cons ':traction_position (traction_position msg))
    (cl:cons ':traction_velocity (traction_velocity msg))
    (cl:cons ':steer_position (steer_position msg))
    (cl:cons ':steer_velocity (steer_velocity msg))
))
