def ply_to_obj(ply_file, obj_file)
  vertices = []
  faces = []
  reading_vertices = false
  reading_faces = false
  vertex_count = 0

  File.open(ply_file, 'r') do |file|
    file.each_line do |line|
      if line.start_with?('end_header')
        reading_vertices = true
      elsif reading_vertices
        v = line.split.map(&:to_f)
        vertices << "v #{v.join(' ')}"
        reading_vertices = false if vertices.size == vertex_count
      elsif reading_faces
        f = line.split[1..-1].map { |i| i.to_i + 1 }.join(' ')
        faces << "f #{f}"
      elsif line.start_with?('element vertex')
        vertex_count = line.split(' ')[-1].to_i
      elsif line.start_with?('element face')
        face_count = line.split(' ')[-1].to_i
        reading_faces = true
      end
    end
  end

  File.open(obj_file, 'w') do |file|
    vertices.each { |v| file.puts(v) }
    faces.each { |f| file.puts(f) }
  end
end

ply_file = 'bunny.ply'
obj_file = 'bunny.obj'
ply_to_obj(ply_file, obj_file)

