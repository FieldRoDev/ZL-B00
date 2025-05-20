; Auto-generated. Do not edit!


(cl:in-package ZL_B00-msg)


;//! \htmlinclude pdo_tx_msgs.msg.html

(cl:defclass <pdo_tx_msgs> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 4 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass pdo_tx_msgs (<pdo_tx_msgs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pdo_tx_msgs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pdo_tx_msgs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ZL_B00-msg:<pdo_tx_msgs> is deprecated: use ZL_B00-msg:pdo_tx_msgs instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <pdo_tx_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ZL_B00-msg:id-val is deprecated.  Use ZL_B00-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <pdo_tx_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ZL_B00-msg:data-val is deprecated.  Use ZL_B00-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pdo_tx_msgs>) ostream)
  "Serializes a message object of type '<pdo_tx_msgs>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id)) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pdo_tx_msgs>) istream)
  "Deserializes a message object of type '<pdo_tx_msgs>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id)) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i 4)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
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
  "e9771f6fc35a81e831d4a03276869531")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pdo_tx_msgs)))
  "Returns md5sum for a message object of type 'pdo_tx_msgs"
  "e9771f6fc35a81e831d4a03276869531")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pdo_tx_msgs>)))
  "Returns full string definition for message of type '<pdo_tx_msgs>"
  (cl:format cl:nil "uint32 id~%uint8[4] data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pdo_tx_msgs)))
  "Returns full string definition for message of type 'pdo_tx_msgs"
  (cl:format cl:nil "uint32 id~%uint8[4] data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pdo_tx_msgs>))
  (cl:+ 0
     4
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pdo_tx_msgs>))
  "Converts a ROS message object to a list"
  (cl:list 'pdo_tx_msgs
    (cl:cons ':id (id msg))
    (cl:cons ':data (data msg))
))
