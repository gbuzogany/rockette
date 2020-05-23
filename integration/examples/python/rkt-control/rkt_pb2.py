# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rkt.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='rkt.proto',
  package='rkt',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=b'\n\trkt.proto\x12\x03rkt\" \n\x0eStatusResponse\x12\x0e\n\x06status\x18\x01 \x01(\x05\"0\n\x0bStringValue\x12\x12\n\nidentifier\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t\"-\n\x08IntValue\x12\x12\n\nidentifier\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\x05\"/\n\nFloatValue\x12\x12\n\nidentifier\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\x02\"/\n\nBytesValue\x12\x12\n\nidentifier\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\x0c\x32\xfb\x01\n\x0fRocketteService\x12\x35\n\rUpdateIntData\x12\r.rkt.IntValue\x1a\x13.rkt.StatusResponse\"\x00\x12\x39\n\x0fUpdateFloatData\x12\x0f.rkt.FloatValue\x1a\x13.rkt.StatusResponse\"\x00\x12;\n\x10UpdateStringData\x12\x10.rkt.StringValue\x1a\x13.rkt.StatusResponse\"\x00\x12\x39\n\x0fUpdateBytesData\x12\x0f.rkt.BytesValue\x1a\x13.rkt.StatusResponse\"\x00\x62\x06proto3'
)




_STATUSRESPONSE = _descriptor.Descriptor(
  name='StatusResponse',
  full_name='rkt.StatusResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='status', full_name='rkt.StatusResponse.status', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=18,
  serialized_end=50,
)


_STRINGVALUE = _descriptor.Descriptor(
  name='StringValue',
  full_name='rkt.StringValue',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='identifier', full_name='rkt.StringValue.identifier', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='rkt.StringValue.value', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=52,
  serialized_end=100,
)


_INTVALUE = _descriptor.Descriptor(
  name='IntValue',
  full_name='rkt.IntValue',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='identifier', full_name='rkt.IntValue.identifier', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='rkt.IntValue.value', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=102,
  serialized_end=147,
)


_FLOATVALUE = _descriptor.Descriptor(
  name='FloatValue',
  full_name='rkt.FloatValue',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='identifier', full_name='rkt.FloatValue.identifier', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='rkt.FloatValue.value', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=149,
  serialized_end=196,
)


_BYTESVALUE = _descriptor.Descriptor(
  name='BytesValue',
  full_name='rkt.BytesValue',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='identifier', full_name='rkt.BytesValue.identifier', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='rkt.BytesValue.value', index=1,
      number=2, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=198,
  serialized_end=245,
)

DESCRIPTOR.message_types_by_name['StatusResponse'] = _STATUSRESPONSE
DESCRIPTOR.message_types_by_name['StringValue'] = _STRINGVALUE
DESCRIPTOR.message_types_by_name['IntValue'] = _INTVALUE
DESCRIPTOR.message_types_by_name['FloatValue'] = _FLOATVALUE
DESCRIPTOR.message_types_by_name['BytesValue'] = _BYTESVALUE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

StatusResponse = _reflection.GeneratedProtocolMessageType('StatusResponse', (_message.Message,), {
  'DESCRIPTOR' : _STATUSRESPONSE,
  '__module__' : 'rkt_pb2'
  # @@protoc_insertion_point(class_scope:rkt.StatusResponse)
  })
_sym_db.RegisterMessage(StatusResponse)

StringValue = _reflection.GeneratedProtocolMessageType('StringValue', (_message.Message,), {
  'DESCRIPTOR' : _STRINGVALUE,
  '__module__' : 'rkt_pb2'
  # @@protoc_insertion_point(class_scope:rkt.StringValue)
  })
_sym_db.RegisterMessage(StringValue)

IntValue = _reflection.GeneratedProtocolMessageType('IntValue', (_message.Message,), {
  'DESCRIPTOR' : _INTVALUE,
  '__module__' : 'rkt_pb2'
  # @@protoc_insertion_point(class_scope:rkt.IntValue)
  })
_sym_db.RegisterMessage(IntValue)

FloatValue = _reflection.GeneratedProtocolMessageType('FloatValue', (_message.Message,), {
  'DESCRIPTOR' : _FLOATVALUE,
  '__module__' : 'rkt_pb2'
  # @@protoc_insertion_point(class_scope:rkt.FloatValue)
  })
_sym_db.RegisterMessage(FloatValue)

BytesValue = _reflection.GeneratedProtocolMessageType('BytesValue', (_message.Message,), {
  'DESCRIPTOR' : _BYTESVALUE,
  '__module__' : 'rkt_pb2'
  # @@protoc_insertion_point(class_scope:rkt.BytesValue)
  })
_sym_db.RegisterMessage(BytesValue)



_ROCKETTESERVICE = _descriptor.ServiceDescriptor(
  name='RocketteService',
  full_name='rkt.RocketteService',
  file=DESCRIPTOR,
  index=0,
  serialized_options=None,
  serialized_start=248,
  serialized_end=499,
  methods=[
  _descriptor.MethodDescriptor(
    name='UpdateIntData',
    full_name='rkt.RocketteService.UpdateIntData',
    index=0,
    containing_service=None,
    input_type=_INTVALUE,
    output_type=_STATUSRESPONSE,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='UpdateFloatData',
    full_name='rkt.RocketteService.UpdateFloatData',
    index=1,
    containing_service=None,
    input_type=_FLOATVALUE,
    output_type=_STATUSRESPONSE,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='UpdateStringData',
    full_name='rkt.RocketteService.UpdateStringData',
    index=2,
    containing_service=None,
    input_type=_STRINGVALUE,
    output_type=_STATUSRESPONSE,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='UpdateBytesData',
    full_name='rkt.RocketteService.UpdateBytesData',
    index=3,
    containing_service=None,
    input_type=_BYTESVALUE,
    output_type=_STATUSRESPONSE,
    serialized_options=None,
  ),
])
_sym_db.RegisterServiceDescriptor(_ROCKETTESERVICE)

DESCRIPTOR.services_by_name['RocketteService'] = _ROCKETTESERVICE

# @@protoc_insertion_point(module_scope)